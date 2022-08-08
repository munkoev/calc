#include "./_test.h"
#include "../smart_calc.h"

START_TEST(trigonometric_1) {
    char input[INPUT_SIZE] = "asin(2)";
    validate(input);
    stack* i = str_to_infix(input);
    stack* p = infix_to_postfix(*i);
    double res = calc_postfix(*p, 0);
    ck_assert_double_nan(res);
    stack_remove(i);
    stack_remove(p);
}
END_TEST

START_TEST(trigonometric_2) {
    char input[INPUT_SIZE] = "3 + sin(cos(tan(0.8))) - acos(asin(atan(0.8))) * sqrt(1.1) / ln(5) ^ log(100)";
    validate(input);
    stack* i = str_to_infix(input);
    stack* p = infix_to_postfix(*i);
    double res = calc_postfix(*p, 0);
    double ori = 3 + sin(cos(tan(0.8))) - acos(asin(atan(0.8))) * sqrt(1.1) / pow(log(5), log10(100));
    ck_assert_double_eq_tol(res, ori, 1e-07);
        stack_remove(i);
    stack_remove(p);
}
END_TEST

START_TEST(trigonometric_3) {
    char input[INPUT_SIZE] = "sqrt(-2)";
    validate(input);
    stack* i = str_to_infix(input);
    stack* p = infix_to_postfix(*i);
    double res = calc_postfix(*p, 0);
    ck_assert_double_nan(res);
        stack_remove(i);
    stack_remove(p);
}
END_TEST

START_TEST(trigonometric_4) {
    char input[INPUT_SIZE] = "ln(0)";
    double res = calc_input(input, 0);
    ck_assert_double_infinite(-res);
}
END_TEST

START_TEST(trigonometric_5) {
    char input[INPUT_SIZE] = "x^2";
    validate(input);
    stack* i = str_to_infix(input);
    stack* p = infix_to_postfix(*i);
    double res = calc_postfix(*p, 6);
    double ori = pow(6,2);
    ck_assert_double_eq_tol(res, ori, 1e-07);
        stack_remove(i);
    stack_remove(p);
}
END_TEST

Suite *suite_trigonometric(void) {
    Suite *s = suite_create("trigonometric");
    TCase *tc = tcase_create("trigonometric");
    tcase_add_test(tc, trigonometric_1);
    tcase_add_test(tc, trigonometric_2);
    tcase_add_test(tc, trigonometric_3);
    tcase_add_test(tc, trigonometric_4);
    tcase_add_test(tc, trigonometric_5);
    suite_add_tcase(s, tc);
    return s;
}
