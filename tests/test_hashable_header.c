#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <check.h>
#include "tcases.h"
#include "tscgi/header.h"
#include "tscgisrv-lua/header.h"

START_TEST(test_hashable_header_list)
{
    struct header_list *list;

    list = create_header_list();

    /* checks appending */
    {
        struct header headers[] =
        {
            {"CONTENT_LENGTH", "0"},
            {"SCGI", "1"},
            {"REQUEST_METHOD", "GET"},
        };
        size_t i;
        size_t len = sizeof(headers) / sizeof(struct header);

        for (i=0; i<len; i++)
            append_header_list(list, &headers[i]);
    }
    {
        /* the header creating context has been unwound. */
        header_t *headers;
        header_t *p, *tmp;

        headers = convert_headers(list);

        HASH_FIND_STR(headers, "SCGI", p);
        ck_assert(p != NULL);
        ck_assert_str_eq(p->value, "1");

        HASH_FIND_STR(headers, "CONTENT_LENGTH", p);
        ck_assert(p != NULL);
        ck_assert_str_eq(p->value, "0");

        HASH_FIND_STR(headers, "REQUEST_METHOD", p);
        ck_assert(p != NULL);
        ck_assert_str_eq(p->value, "GET");
    }

    destory_header_list(list);
}
END_TEST

TCase * tcase_hashable_header(void)
{
    TCase *tcase = tcase_create("hashable_header");
    tcase_add_test(tcase, test_hashable_header_list);
    return tcase;
}
