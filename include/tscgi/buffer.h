#ifndef _TINYSCGI_BUFFER_H
#define _TINYSCGI_BUFFER_H

#define EMPTY_BUFFER ("\0")

struct buffer
{
    void *ptr;
    size_t len;
    int pos;
};

extern void buffer_init(struct buffer *buffer, void *ptr, size_t len);
extern inline size_t buffer_pos(struct buffer *buffer);
extern inline size_t buffer_len(struct buffer *buffer);
extern inline char buffer_getc(struct buffer *buffer);
extern inline size_t buffer_forward(struct buffer *buffer, size_t offset);
extern inline void *buffer_current(struct buffer *buffer);

#endif
