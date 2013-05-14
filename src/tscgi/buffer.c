#include <stdlib.h>
#include "buffer.h"

void buffer_init(struct buffer *buffer, void *ptr, size_t len)
{
    buffer->ptr = ptr;
    buffer->len = len;
    buffer->pos = 0;
}

inline size_t buffer_pos(struct buffer *buffer)
{
    return buffer->pos;
}

inline size_t buffer_forward(struct buffer *buffer, size_t offset)
{
    if (offset && (buffer->pos >= 0))
        buffer->pos += offset;
    if (buffer->pos >= buffer->len)
        buffer->pos = -1;  /* overflow */
    return buffer->pos;
}

inline void *buffer_current(struct buffer *buffer)
{
    return (buffer->pos >= 0) ? (buffer->ptr + buffer->pos) : EMPTY_BUFFER;
}
