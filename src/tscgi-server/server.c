#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include "server.h"
#include "../tscgi/errors.h"
#include "../tscgi/buffer.h"
#include "../tscgi/request.h"

static void on_connect(uv_stream_t *server, int status);
static void on_connect_error(uv_loop_t *loop, int uv_errno);
static void on_request(uv_stream_t *client, ssize_t nread, uv_buf_t buf);
static void on_response_end(uv_write_t *response, int status);
static uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size);


/**
 * The callback function to allocate memory and create buffer area.
 */
static uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size)
{
    return uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

/**
 * The callback function while server socket listening. It accepts connection
 * from client and reads request data.
 */
static void on_connect(uv_stream_t *server, int status)
{
    if (status == -1)
        return;

    uv_tcp_t *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(uv_default_loop(), client);

    if (uv_accept(server, (uv_stream_t *) client) == 0)
    {
        client->data = server->data;
        uv_read_start((uv_stream_t *) client, alloc_buffer, on_request);
    }
    else
    {
        uv_close((uv_handle_t*) client, NULL);
    }
}

static void on_connect_error(uv_loop_t *loop, int uv_errno)
{
    fprintf(stderr, "listen error: %s\n", uv_err_name(uv_last_error(loop)));
    exit(EXIT_FAILURE);
}

static void on_request(uv_stream_t *client, ssize_t nread, uv_buf_t buf)
{
    struct buffer request_buffer, response_buffer;
    struct request request;

    if (nread == -1)
    {
        /* process file descriptor EOF */
        if (uv_last_error(uv_default_loop()).code == UV_EOF)
            uv_close((uv_handle_t *) client, NULL);
    }
    else if (nread > 0)
    {
        {
            int rv;
            struct scgi_server *s;

            s = (struct scgi_server *) client->data;  /* unpack scgi_server */

            buffer_init(&request_buffer, buf.base, nread);
            rv = parse_request(&request_buffer, &request, 4096);
            if (rv != REQUEST_OK)
            {
                /*tscgi_perror(rv); FIXME: error handle */
                /*goto request_finished;*/
            }

            /* process request by predefined hook function */
            s->process_request(s, &request, &response_buffer);

            uv_read_stop(client);
        }

        /* send response */
        {
            uv_buf_t *uv_response_buffer;
            uv_write_t *response;

            uv_response_buffer = malloc(sizeof(uv_buf_t));
            uv_response_buffer->base = buffer_current(&response_buffer);
            uv_response_buffer->len = buffer_len(&response_buffer);

            response = malloc(sizeof(uv_write_t));
            response->data = (void *) client;

            uv_write(response, client, uv_response_buffer, 1, on_response_end);
        }

        /* release memory allocated by `alloc_buffer` */
        uv_read_stop(client);
        if (buf.base)
            free(buf.base);
    }
}

static void on_response_end(uv_write_t *response, int status)
{
    if (response)
    {
        uv_close((uv_handle_t *) response->data, NULL);
        free(response);
    }
}

void listen_scgi_server(struct scgi_server s)
{
    int uv_errno, i;
    uv_tcp_t tcp;

    /* initialize tcp socket and bind it to prepared addresses */
    uv_tcp_init(s.loop, &tcp);
    for (i=0; i<s.nbind_addrs; i++)
        uv_tcp_bind(&tcp, s.bind_addrs[i]);

    tcp.data = (void *) &s;  /* pack scgi_server */

    uv_errno = uv_listen((uv_stream_t *) &tcp, s.max_conn, on_connect);
    if (uv_errno)
        on_connect_error(s.loop, uv_errno);
    else
        uv_run(s.loop, UV_RUN_DEFAULT);
}
