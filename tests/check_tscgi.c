#include <stdlib.h>
#include <check.h>
#include "../src/tscgi/request.h"
#include "tcases.h"

Suite * tinyscgi_suite(void)
{
    Suite *suite = suite_create("tinyscgi");
    suite_add_tcase(suite, tcase_netstring());
    suite_add_tcase(suite, tcase_header());
    suite_add_tcase(suite, tcase_request());
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
