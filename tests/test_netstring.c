#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <check.h>
#include "tcases.h"
#include "../src/netstring.h"

START_TEST(test_parse_netstring)
    const char *expect_buffer_value =
        "CONTENT_LENGTH" "\0" "27" "\0"
        "SCGI" "\0" "1" "\0"
        "REQUEST_METHOD" "\0" "POST" "\0"
        "REQUEST_URI" "\0" "/deepthought" "\0";
    const char *path_t1 = "./data/test_netstring_1.txt";
{
    FILE *stream;
    char *buffer;
    int ret;

    stream = fopen(path_t1, "r");
    fail_if(stream == NULL, strerror(errno));

    ret = parse_netstring(stream, &buffer);
    fail_unless(ret == NETSTRING_OK);

    fclose(stream);

    ck_assert_str_eq(buffer, expect_buffer_value);

    destory_netstring(buffer);
}
END_TEST

TCase * tcase_netstring(void)
{
    TCase *tcase = tcase_create("netstring");
    tcase_add_test(tcase, test_parse_netstring);
    return tcase;
}
