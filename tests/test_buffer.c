#include <check.h>
#include <stdlib.h>
#include "tcases.h"
#include "../src/tscgi/buffer.h"

START_TEST(test_buffer)
{
    char *str;
    size_t i;

    str = (char *) malloc(10);
    {
        for (i=0; i<10; i++)
            str[i] = 'a';
        str[i] = '\0';

        {
            struct buffer buf;
            buffer_init(&buf, str, 10);

            /* testing initialize */
            ck_assert(buffer_current(&buf) == str);
            ck_assert(buffer_len(&buf) == 10);
            ck_assert(buffer_pos(&buf) == 0);
            ck_assert_str_eq(buffer_current(&buf), "aaaaaaaaaa");

            /* testing forward */
            buffer_forward(&buf, 2);
            ck_assert(buffer_pos(&buf) == 2);
            ck_assert_str_eq(buffer_current(&buf), "aaaaaaaa");

            buffer_forward(&buf, 4);
            ck_assert(buffer_pos(&buf) == 6);
            ck_assert_str_eq(buffer_current(&buf), "aaaa");

            buffer_forward(&buf, 2);
            ck_assert(buffer_pos(&buf) == 8);
            ck_assert_str_eq(buffer_current(&buf), "aa");

            /* testing getc */
            ck_assert(buffer_getc(&buf) == 'a');
            ck_assert(buffer_pos(&buf) == 9);
            ck_assert_str_eq(buffer_current(&buf), "a");

            /* testing overflow */
            buffer_forward(&buf, 1);
            ck_assert(buffer_pos(&buf) == -1);
            ck_assert_str_eq(buffer_current(&buf), "");

            buffer_forward(&buf, 0);
            ck_assert(buffer_pos(&buf) == -1);
            ck_assert_str_eq(buffer_current(&buf), "");

            buffer_forward(&buf, 15);
            ck_assert(buffer_pos(&buf) == -1);
            ck_assert_str_eq(buffer_current(&buf), "");
        }
    }
    free(str);
}
END_TEST

START_TEST(test_eof_getc_bug)
{
    /* A bug has been fixed: use buffer_getc before eof will get empty */
    struct buffer buf;

    buffer_init(&buf, "abc#", 4);
    buffer_forward(&buf, 3);

    ck_assert(buffer_getc(&buf) == '#');
}
END_TEST

TCase * tcase_buffer(void)
{
    TCase *tcase = tcase_create("buffer");
    tcase_add_test(tcase, test_buffer);
    tcase_add_test(tcase, test_eof_getc_bug);
    return tcase;
}
