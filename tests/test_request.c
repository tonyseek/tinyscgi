#include <check.h>
#include "tcases.h"
#include "../src/errors.h"
#include "../src/netstring.h"
#include "../src/header.h"
#include "../src/request.h"

START_TEST(test_parse_request)
{
}
END_TEST

TCase * tcase_request(void)
{
    TCase *tcase = tcase_create("request");
    tcase_add_test(tcase, test_parse_request);
    return tcase;
}
