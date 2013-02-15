#include <stdlib.h>
#include <check.h>
#include "../src/request.h"

START_TEST(test_header_list)
{
    struct header_list *list;

    list = create_header_list();
    fail_unless(list->item.name == NULL, "the list field is not clean.");
    fail_unless(list->item.value == NULL, "the list field is not clean.");
    fail_unless(list->next == NULL, "the next pointer is not clean.");
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
