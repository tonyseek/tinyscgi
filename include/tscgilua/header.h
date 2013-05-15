#ifndef _TINYSCGI_SERVER_LUA_HEADER_H
#define _TINYSCGI_SERVER_LUA_HEADER_H

#include "uthash.h"
#include "tscgi/header.h"

#define SIZE_OF_HEADER_T (sizeof(struct hashable_header))

struct hashable_header
{
    char *name;
    char *value;
    UT_hash_handle hh;
};

typedef struct hashable_header header_t;

extern header_t * convert_headers(struct header_list *);

#endif
