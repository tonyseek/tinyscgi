#include <check.h>
#include "tcases.h"
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

    destory_header_list(list);
}
END_TEST

TCase * tcase_request(void)
{
    TCase *tcase = tcase_create("request");
    tcase_add_test(tcase, test_header_list);
    return tcase;
}
