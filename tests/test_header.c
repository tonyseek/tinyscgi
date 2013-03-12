#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <check.h>
#include "tcases.h"
#include "../src/scgi/errors.h"
#include "../src/scgi/netstring.h"
#include "../src/scgi/header.h"
#include "../src/scgi/request.h"

START_TEST(test_header_list)
{
    struct header_list *list;

    list = create_header_list();

    /* checks initial values */
    {
        fail_unless(list->item.name == NULL);
        fail_unless(list->item.value == NULL);
        fail_unless(list->next == NULL);
    }

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
        struct header_list *l;
        /* 0 */
        l = list;
        fail_unless(l->item.name == NULL);
        fail_unless(l->item.value == NULL);
        /* 1 */
        l = l->next;
        ck_assert_str_eq(l->item.name, "CONTENT_LENGTH");
        ck_assert_str_eq(l->item.value, "0");
        /* 2 */
        l = l->next;
        ck_assert_str_eq(l->item.name, "SCGI");
        ck_assert_str_eq(l->item.value, "1");
        /* 3 */
        l = l->next;
        ck_assert_str_eq(l->item.name, "REQUEST_METHOD");
        ck_assert_str_eq(l->item.value, "GET");
        /* last */
        fail_unless(l->next == NULL);
    }

    destory_header_list(list);
}
END_TEST

START_TEST(test_parse_request_header)
{
    FILE *stream;
    char *buffer;
    size_t len;
    int ret;
    struct request request;

    stream = fopen(TEST_NETSTRING_PATH_1, "r");
    {
        fail_if(stream == NULL, strerror(errno));
        ret = parse_netstring(stream, &buffer, &len);
        {
            fail_unless(ret == NETSTRING_OK);

            request.headers = create_header_list();
            {
                /* parse headers */
                parse_headers((const char *) buffer, len, request.headers);
                /* allocate body spcae */
                request.body = (char *) malloc(4096);
                {
                    fread(request.body, sizeof(char), 4096, stream);

                    /* check the request headers */
                    check_headers_for_42((void *) request.headers);

                    /* check the request body */
                    ck_assert_str_eq(request.body,
                                     "What is the answer to life?\n");
                }
                free(request.body);
            }
            destory_header_list(request.headers);
        }
        destory_netstring(buffer);
    }
    fclose(stream);
}
END_TEST

TCase * tcase_header(void)
{
    TCase *tcase = tcase_create("header");
    tcase_add_test(tcase, test_header_list);
    tcase_add_test(tcase, test_parse_request_header);
    return tcase;
}

void check_headers_for_42(void *data)
{
    struct header_list *list;

    list = (struct header_list *) data;

    /* 0 */
    ck_assert_str_eq(list->item.name, "CONTENT_LENGTH");
    ck_assert_str_eq(list->item.value, "27");

    /* 1 */
    list = list->next;
    ck_assert_str_eq(list->item.name, "SCGI");
    ck_assert_str_eq(list->item.value, "1");

    /* 2 */
    list = list->next;
    ck_assert_str_eq(list->item.name, "REQUEST_METHOD");
    ck_assert_str_eq(list->item.value, "POST");

    /* 3 */
    list = list->next;
    ck_assert_str_eq(list->item.name, "REQUEST_URI");
    ck_assert_str_eq(list->item.value, "/deepthought");

    /* last */
    printf("[%X]", list->next);
    fail_unless(list->next == NULL);
}
