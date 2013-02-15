#include <stdio.h>
#include <stdlib.h>
#include "request.h"

struct header_list * create_header_list()
{
    struct header_list *list;

    list = (struct header_list *) malloc(sizeof(struct header_list));
    if (!list)
    {
        perror("could not create header list");
        abort();
    }

    list->item.name = NULL;
    list->item.value = NULL;
    list->next = NULL;

    return list;
}

void destory_header_list(struct header_list *list)
{
    struct header_list *current, *next;

    current = list;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

int append_header_list(struct header_list *list, struct header *item)
{
    while (list->next)
        list = list->next;

    list->next = create_header_list();
    list->next->item = *item;

    return 0;
}
