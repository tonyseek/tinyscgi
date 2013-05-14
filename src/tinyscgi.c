#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include "tscgi/errors.h"
#include "tscgi/buffer.h"
#include "tscgi/request.h"
#include "tscgi/header.h"

uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size)
{
    return uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

void tscgi_perror(int rv)
{
    fprintf(stderr, "ERROR[%x]: ", rv);
    if (rv & NETSTRING_ERROR_STREAM)
        fprintf(stderr, "netstring error stream.\n");
    if (rv & NETSTRING_ERROR_FORMAT)
        fprintf(stderr, "netstring error format.\n");
    if (rv & REQUEST_ERROR_CONTENT_LENGTH)
        fprintf(stderr, "request error content length.\n");
    if (rv & REQUEST_ERROR_BROKEN_PIPE)
        fprintf(stderr, "request error broken pipe.\n");
    if (rv & REQUEST_ERROR_BODY_TOO_MAX)
        fprintf(stderr, "request error body too max.\n");
}

void after_response(uv_write_t *resp, int status)
{
    uv_close((uv_handle_t *) resp->data, NULL);
}

void on_request(uv_stream_t *stream, ssize_t nread, uv_buf_t buf)
{
    int rv;
    size_t i;
    struct buffer buffer;
    struct request request;
    struct header_list *headers;

    if (nread == -1)
    {
        if (uv_last_error(uv_default_loop()).code == UV_EOF)
            uv_close((uv_handle_t *) stream, NULL);
    }
    else if (nread > 0)
    {
        buffer_init(&buffer, buf.base, nread);
        rv = parse_request(&buffer, &request, 4096);
        if (rv != REQUEST_OK)
        {
            tscgi_perror(rv);
            goto request_finished;
        }

        printf("\n# request headers\n");
        headers = request.headers;
        do
        {
            printf("#### %s :: %s\n", headers->item.name, headers->item.value);
            headers = headers->next;
        }
        while (headers);

        if (strlen(request.body))
        {
            printf("# request body\n");
            printf("##### %s\n", request.body);
        }

        /* send response */
        {
            uv_buf_t rbuf;
            uv_write_t resp;

            rbuf.base = "Status: 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "\r\n"
                        "hello, world.\n";
            rbuf.len = strlen(rbuf.base);
            resp.data = (void *) stream;

            uv_write(&resp, stream, &rbuf, 1, after_response);
        }
    }

request_finished:
    uv_read_stop(stream);
    if (buf.base)
        free(buf.base);
    return;

request_error:
    goto request_finished;
}

void on_new_connection(uv_stream_t *server, int status)
{
    if (status == -1)
        return;

    uv_tcp_t *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(uv_default_loop(), client);

    if (uv_accept(server, (uv_stream_t *) client) == 0)
        uv_read_start((uv_stream_t *) client, alloc_buffer, on_request);
    else
        uv_close((uv_handle_t*) client, NULL);
}


int main(int argc, char **argv)
{
    int uv_err;
    uv_loop_t *loop;

    loop = uv_default_loop();
    {
        uv_tcp_t server;
        uv_tcp_init(loop, &server);
        uv_tcp_bind(&server, uv_ip4_addr("0.0.0.0", 8000));

        uv_err = uv_listen((uv_stream_t *) &server, 128, on_new_connection);
        if (uv_err)
        {
            fprintf(stderr, "listen error: %s\n",
                    uv_err_name(uv_last_error(loop)));
            return EXIT_FAILURE;
        }
    }
    uv_run(loop, UV_RUN_DEFAULT);

    return EXIT_SUCCESS;
}
