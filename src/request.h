#ifndef _TINYSCGI_REQUEST_H
#define _TINYSCGI_REQUEST_H

struct header
{
    char *name;
    char *value;
};

struct header_list
{
    struct header item;
    struct header_list *next;
};

struct request
{
    struct header_list *headers;
    char *body;
};

#endif
