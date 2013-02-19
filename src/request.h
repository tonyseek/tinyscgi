#ifndef _TINYSCGI_REQUEST_H
#define _TINYSCGI_REQUEST_H

#include "header.h"

struct request
{
    struct header_list *headers;
    char *body;
};

#endif
