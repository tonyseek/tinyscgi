#ifndef _TINYSCGI_REQUEST_H
#define _TINYSCGI_REQUEST_H

#include <stdio.h>
#include "header.h"

struct request
{
    struct header_list *headers;
    char *body;
    /* private */
    char *_headers_buffer;
};

struct buffer;

extern int parse_request(struct buffer *, struct request *, size_t);
extern int destory_request(struct request *);

#endif
