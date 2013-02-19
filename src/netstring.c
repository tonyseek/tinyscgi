#include <stdio.h>
#include <stdlib.h>
#include "netstring.h"

int parse_netstring(FILE *stream, char **buffer)
{
    size_t len;
    char *buf;

    if (fscanf(stream, "%9lu", &len) < 1)
        return NETSTRING_ERROR_STREAM;

    if (getc(stream) != ':')
        return NETSTRING_ERROR_FORMAT;

    buf = (char *) malloc(len + 1);
    if (!buf)
        return NETSTRING_ERROR_NOMEM;

    if (fread(buf, sizeof(char), len, stream) < len)
        return NETSTRING_ERROR_STREAM;

    if (getc(stream) != ',')
        return NETSTRING_ERROR_FORMAT;

    *buffer = buf;

    return NETSTRING_OK;
}

void destory_netstring(char *buffer)
{
    free(buffer);
}
