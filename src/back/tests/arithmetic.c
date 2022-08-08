#include "./_test.h"
#include "../smart_calc.h"

START_TEST(arithmetic_1) {
    char input[INPUT_SIZE] = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    validate(input);
    stack* i = str_to_infix(input);
    stack* p = infix_to_postfix(*i);
    double res = calc_postfix(*p, 0);
    double ori = 3 + 8.0 / pow(-4, 8);
    ck_assert_double_eq_tol(res, ori, 1e-07);
        stack_remove(i);
    stack_remove(p);
}
END_TEST

START_TEST(arithmetic_2) {
    char input[INPUT_SIZE] = "3 + 5 mod (6 - 5.4)";
    validate(input);
    stack* i = str_to_infix(input);
    stack* p = infix_to_postfix(*i);
    double res = calc_postfix(*p, 0);
    double ori = 3 + fmod(5, 0.6);
    ck_assert_double_eq_tol(res, ori, 1e-07);
        stack_remove(i);
    stack_remove(p);
}
END_TEST

Suite *suite_arithmetic(void) {
    Suite *s = suite_create("arithmetic");
    TCase *tc = tcase_create("arithmetic");
    tcase_add_test(tc, arithmetic_1);
    tcase_add_test(tc, arithmetic_2);
    suite_add_tcase(s, tc);
    return s;
}
