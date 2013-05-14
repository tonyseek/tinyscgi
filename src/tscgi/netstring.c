#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "netstring.h"
#include "buffer.h"

int parse_netstring(struct buffer *stream, char **buffer, size_t *length)
{
    char *buf;
    size_t len;
    int rv, nscanf;

    rv = sscanf(buffer_current(stream), "%9lu%n", &len, &nscanf);
    if (rv != 1 || nscanf <= 0)
        return NETSTRING_ERROR_STREAM;
    else
        buffer_forward(stream, nscanf);

    if (buffer_getc(stream) != ':')
        return NETSTRING_ERROR_FORMAT;

    buf = (char *) malloc(len + 1);
    if (!buf)
        return NETSTRING_ERROR_NOMEM;

    if (buffer_len(stream) - buffer_pos(stream) < len + 1)
    {
        free(buf);
        return NETSTRING_ERROR_STREAM;
    }
    else
    {
        memcpy(buf, buffer_current(stream), len);
        buffer_forward(stream, len);
    }

    if (buffer_getc(stream) != ',')
    {
        free(buf);
        return NETSTRING_ERROR_FORMAT;
    }

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
