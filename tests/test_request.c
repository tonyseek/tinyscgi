#include <stdio.h>
#include <check.h>
#include "tcases.h"
#include "../src/tscgi/errors.h"
#include "../src/tscgi/netstring.h"
#include "../src/tscgi/header.h"
#include "../src/tscgi/request.h"

START_TEST(test_parse_request)
{
    FILE *stream;
    struct request r;

    stream = fopen(TEST_NETSTRING_PATH_1, "r");
    {
        parse_request(stream, &r, 4096);
        {
            check_headers_for_42((void *) r.headers);
            ck_assert_str_eq(r.body, "What is the answer to life?");
        }
        destory_request(&r);
    }
    fclose(stream);
}
END_TEST

TCase * tcase_request(void)
{
    TCase *tcase = tcase_create("request");
    tcase_add_test(tcase, test_parse_request);
    return tcase;
}
