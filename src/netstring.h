#ifndef _TINYSCGI_NETSTRING_H
#define _TINYSCGI_NETSTRING_H

#include <stdio.h>

#define NETSTRING_OK              (-0x0000)
#define NETSTRING_ERROR_FORMAT    (-0x0001)
#define NETSTRING_ERROR_NOMEM     (-0x0002)
#define NETSTRING_ERROR_STREAM    (-0x0003)

extern int parse_netstring(FILE *, char **);
extern void destory_netstring(char *);

#endif
