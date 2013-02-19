#ifndef _TINYSCGI_NETSTRING_H
#define _TINYSCGI_NETSTRING_H

#include <stdio.h>

extern int parse_netstring(FILE *, char **, size_t *);
extern void destory_netstring(char *);

#endif
