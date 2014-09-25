#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include "tscgi/buffer.h"
#include "tscgi/header.h"
#include "tscgi/request.h"
#include "tscgisrv/server.h"

void process_hello_request(struct scgi_server *s, struct request *request,
                           struct buffer *response_buffer)
{
    struct header_list *h;
    char *resp = malloc(1024);

    h = request->headers;
    while (NULL != (h = h->next))
    {
        if (h->item.name && 0 == strcmp(h->item.name, "REQUEST_URI"))
        {
            sprintf(resp, "Status: 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                          "ROUTE[%s]", h->item.value);
        }
    }

    printf("==\n%s\n==", resp);

    buffer_init(response_buffer, resp, strlen(resp));
}

void init_hello_scgi_server(struct scgi_server *s)
{
    s->loop = uv_default_loop();
    s->max_conn = 128;
    s->process_request = &process_hello_request;
    s->process_bad_request = NULL;

    s->bind_addrs[0] = uv_ip4_addr("0.0.0.0", 8000);
    s->nbind_addrs = 1;
}

int main(int argc, char **argv)
{
    struct scgi_server s;

    init_hello_scgi_server(&s);
    listen_scgi_server(s);

    return EXIT_SUCCESS;
}
