#include <stdio.h>
#include <stdlib.h>
#include "netstring.h"

int parse_netstring(FILE *stream, char **buffer, size_t *length)
{
    char *buf;
    size_t len;

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

    /* out parameter */
    if (buffer)
        *buffer = buf;
    if (length)
        *length = len;

    return NETSTRING_OK;
}

void destory_netstring(char *buffer)
{
    free(buffer);
}
