#ifndef _TINYSCGI_TCASES_H
#define _TINYSCGI_TCASES_H

TCase * tcase_request(void);
TCase * tcase_netstring(void);

#define TEST_NETSTRING_PATH_1 "./data/test_netstring_1.txt"

#endif
