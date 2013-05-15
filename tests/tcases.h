#ifndef _TINYSCGI_TCASES_H
#define _TINYSCGI_TCASES_H

TCase * tcase_netstring(void);
TCase * tcase_header(void);
TCase * tcase_request(void);
TCase * tcase_buffer(void);
TCase * tcase_hashable_header(void);

#define TEST_NETSTRING_PATH_1 "./data/test_netstring_1.txt"

extern void check_headers_for_42(void *);

#endif
