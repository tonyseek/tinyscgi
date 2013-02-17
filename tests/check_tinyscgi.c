#include <stdlib.h>
#include <check.h>
#include "../src/request.h"

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
        fail_unless(l->item.name == "CONTENT_LENGTH");
        fail_unless(l->item.value == "0");
        /* 2 */
        l = l->next;
        fail_unless(l->item.name == "SCGI");
        fail_unless(l->item.value == "1");
        /* 3 */
        l = l->next;
        fail_unless(l->item.name == "REQUEST_METHOD");
        fail_unless(l->item.value == "GET");
        /* last */
        fail_unless(l->next == NULL);
    }
}
END_TEST

Suite * tinyscgi_suite(void)
{
    Suite *suite = suite_create("tinyscgi");

    /* request.c */
    TCase *tcase_reuqest = tcase_create("request");
    tcase_add_test(tcase_reuqest, test_header_list);
    suite_add_tcase (suite, tcase_reuqest);

    return suite;
}

int main(void)
{
    int failed_num;
    Suite *suite;
    SRunner *runner;

    suite = tinyscgi_suite();
    runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    failed_num = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed_num == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
