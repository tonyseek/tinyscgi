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

extern int parse_request(FILE *, struct request *, size_t);
extern int destory_request(struct request *);

#endif
