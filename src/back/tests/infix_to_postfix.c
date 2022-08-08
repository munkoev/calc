#include "./_test.h"
#include "../smart_calc.h"

START_TEST(str_to_infix_1) {
    char input[INPUT_SIZE] = " -5 + sin(cos(2.1)) * 6";
    int v = validate(input);
    stack* s = str_to_infix(input);
    int q = s->array[0].type;
    double a = s->array[s->top].value;
    ck_assert_int_eq(v, 0);
    ck_assert_int_eq(q, 0);
    ck_assert_double_eq(a, 6.0);
        stack_remove(s);
}
END_TEST

START_TEST(infix_to_postfix_1) {
    char input[INPUT_SIZE] = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    int v = validate(input);
    stack* i = str_to_infix(input);
    stack* p = infix_to_postfix(*i); // 3 4 2 * 1 5 − 2 3 ^ ^ / +
    ck_assert_int_eq(v, 0);
    ck_assert_int_eq(p->array[p->top].type, 2);
        stack_remove(i);
    stack_remove(p);
}
END_TEST

START_TEST(infix_to_postfix_2) {
    char input[INPUT_SIZE] = "sin ( cos ( 2 ) / 3 * x )";
    int v = validate(input);
    stack* i = str_to_infix(input);
    stack* p = infix_to_postfix(*i);  // 2 cos 3 / x * sin
    ck_assert_int_eq(v, 0);
    ck_assert_int_eq(p->array[p->top].type, 9);
        stack_remove(i);
    stack_remove(p);
}
END_TEST

Suite *suite_infix_to_postfix(void) {
    Suite *s = suite_create("infix_to_postfix");
    TCase *tc = tcase_create("infix_to_postfix");
    tcase_add_test(tc, str_to_infix_1);
    tcase_add_test(tc, infix_to_postfix_1);
    tcase_add_test(tc, infix_to_postfix_2);
    suite_add_tcase(s, tc);
    return s;
}
