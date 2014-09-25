#include <stdio.h>
#include <check.h>
#include "tcases.h"
#include "tscgi/errors.h"
#include "tscgi/netstring.h"
#include "tscgi/header.h"
#include "tscgi/request.h"
#include "tscgi/buffer.h"

START_TEST(test_parse_request)
{
    FILE *file;
    char file_buffer[256];
    struct buffer stream;
    struct request r;
    char *buffer;
    size_t length;

    file = fopen(TEST_NETSTRING_PATH_1, "r");
    {
        length = fread(file_buffer, 1, 256, file);
        buffer_init(&stream, file_buffer, length);
        parse_request(&stream, &r, 4096);
        {
            check_headers_for_42((void *) r.headers);
            ck_assert_str_eq(r.body, "What is the answer to life?");
        }
        destory_request(&r);
    }
    fclose(file);
}
END_TEST

TCase * tcase_request(void)
{
    TCase *tcase = tcase_create("request");
    tcase_add_test(tcase, test_parse_request);
    return tcase;
}
