#ifndef _TINYSCGI_ERRORS_H
#define _TINYSCGI_ERRORS_H

#define NETSTRING_OK                      (0)
#define NETSTRING_ERROR_FORMAT            (0x0001)
#define NETSTRING_ERROR_NOMEM             (0x0002)
#define NETSTRING_ERROR_STREAM            (0x0003)

#define REQUEST_OK                        (0)
#define REQUEST_ERROR_CONTENT_LENGTH      (0x0010)
#define REQUEST_ERROR_BODY_TOO_MAX        (0x0020)

#endif
