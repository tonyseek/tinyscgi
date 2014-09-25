#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <check.h>
#include "tcases.h"
#include "tscgi/errors.h"
#include "tscgi/netstring.h"
#include "tscgi/buffer.h"

START_TEST(test_parse_netstring)
    const char *expect_buffer_value =
        "CONTENT_LENGTH" "\0" "27" "\0"
        "SCGI" "\0" "1" "\0"
        "REQUEST_METHOD" "\0" "POST" "\0"
        "REQUEST_URI" "\0" "/deepthought" "\0";
{
    struct buffer stream;
    FILE *file;
    char file_buffer[256];
    char *buffer;
    size_t length;
    int ret;

    file = fopen(TEST_NETSTRING_PATH_1, "r");
    ck_assert_msg(file != NULL, strerror(errno));

    length = fread(file_buffer, 1, 256, file);
    ck_assert_msg(length >= 0, strerror(errno));
    buffer_init(&stream, file_buffer, length);

    ret = parse_netstring(&stream, &buffer, NULL);
    ck_assert(ret == NETSTRING_OK);

    fclose(file);

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
