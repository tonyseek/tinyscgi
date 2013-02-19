#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "netstring.h"
#include "header.h"
#include "request.h"

int parse_request(FILE *stream, struct request *request, size_t body_max_len)
{
    int ret;
    char *headers_buffer, *body_buffer;
    size_t headers_len;
    struct header_list *headers;

    /* parse netstring */
    ret = parse_netstring(stream, &headers_buffer, &headers_len);
    if (ret != NETSTRING_OK)
        return ret;

    /* create header list and parse headers */
    headers = create_header_list();
    parse_headers((const char *) headers_buffer, headers_len, headers);

    /* read body */
    body_buffer = (char *) malloc(body_max_len);
    memset(body_buffer, 0, body_max_len);
    fread(body_buffer, sizeof(char), body_max_len, stream);

    /* save public attributes */
    request->headers = headers;
    request->body = body_buffer;

    /* save private resource handle */
    request->_headers_buffer = headers_buffer;
}

int destory_request(struct request *request)
{
    destory_header_list(request->headers);
    free(request->body);
    free(request->_headers_buffer);
}
