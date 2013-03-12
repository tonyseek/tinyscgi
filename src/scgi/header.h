#ifndef _TINYSCGI_HEADER_H
#define _TINYSCGI_HEADER_H

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

extern struct header_list * create_header_list();
extern void destory_header_list(struct header_list *);
extern int append_header_list(struct header_list *, struct header *);
extern int parse_headers(const char *, size_t, struct header_list *);

#endif
