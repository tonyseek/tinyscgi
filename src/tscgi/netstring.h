#ifndef _TINYSCGI_NETSTRING_H
#define _TINYSCGI_NETSTRING_H

#include <stdio.h>

struct buffer;

extern int parse_netstring(struct buffer *, char **, size_t *);
extern void destory_netstring(char *);

#endif
