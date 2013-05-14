#ifndef _TINYSCGI_BUFFER_H
#define _TINYSCGI_BUFFER_H

struct buffer;

extern void buffer_init(struct buffer *buffer, void *ptr, size_t len);
extern inline size_t buffer_pos(struct buffer *buffer);
extern inline size_t buffer_seek(struct buffer *buffer, size_t offset);
extern inline void *buffer_current(struct buffer *buffer);

#endif
