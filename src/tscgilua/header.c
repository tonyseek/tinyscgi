#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tscgilua/header.h"

header_t * convert_headers(struct header_list *linked_headers)
{
    struct header_list *ptr = linked_headers;
    header_t *h, *_headers = NULL;

    while ((ptr = ptr->next) != NULL)
    {
        if (ptr->item.name && strlen(ptr->item.name))
        {
            h = malloc(SIZE_OF_HEADER_T);
            h->name = ptr->item.name;
            h->value = ptr->item.value;

            HASH_ADD_KEYPTR(hh, _headers, h->name, strlen(h->name), h);
        }
    }

    return _headers;
}
