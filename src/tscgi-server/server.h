#ifndef _TINYSCGI_SERVER_SERVER_H
#define _TINYSCGI_SERVER_SERVER_H

struct request;
struct buffer;

struct response
{
    struct request *request;
    uv_stream_t *client;
};

struct scgi_server
{
    uv_loop_t *loop;

    struct sockaddr_in bind_addrs[20];
    size_t nbind_addrs;

    size_t max_conn;

    void (*process_request)(struct scgi_server *, struct request *,
                            struct buffer *);
};

extern void listen_scgi_server(struct scgi_server);

#endif
