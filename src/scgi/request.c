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
    size_t headers_len, body_len;
    struct header_list *headers;

    /* parse netstring */
    ret = parse_netstring(stream, &headers_buffer, &headers_len);
    if (ret != NETSTRING_OK)
        return ret;

    /* create header list and parse headers */
    headers = create_header_list();
    parse_headers((const char *) headers_buffer, headers_len, headers);

    /* the first header must be content length */
    if (strcmp(headers->item.name, "CONTENT_LENGTH") != 0)
        return REQUEST_ERROR_CONTENT_LENGTH;
    body_len = atoi(headers->item.value);
    /* failed to convert digest */
    if (body_len <= 0 && strcmp(headers->item.value, "0") != 0)
        return REQUEST_ERROR_CONTENT_LENGTH;

    /* read body */
    if (body_len > body_max_len)
        return REQUEST_ERROR_BODY_TOO_MAX;
    if (body_len)
    {
        body_buffer = (char *) malloc(body_len);
        memset(body_buffer, 0, body_len);
        fread(body_buffer, sizeof(char), body_len, stream);
    }
    else
    {
        body_buffer = "";
    }

    /* save public attributes */
    request->headers = headers;
    request->body = body_buffer;

    /* save private resource handle */
    request->_headers_buffer = headers_buffer;

    return REQUEST_OK;
}

int destory_request(struct request *request)
{
    if (request->headers)
        destory_header_list(request->headers);
    if (request->body && request->body[0])
        free(request->body);
    if (request->_headers_buffer && request->_headers_buffer[0])
        free(request->_headers_buffer);
}
