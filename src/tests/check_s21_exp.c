#include "check_s21_exp.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

#define RANGE 10

START_TEST(zero_check_s21_exp) {
  ck_assert_ldouble_eq_tol(exp(0.0), s21_exp(0.0), S21_PRECISION);
}
END_TEST

START_TEST(inf_check_s21_exp) { ck_assert_ldouble_infinite(s21_exp(S21_INF)); }
END_TEST

START_TEST(nan_check_s21_exp) { ck_assert_ldouble_nan(s21_exp(S21_NAN)); }
END_TEST

START_TEST(step_check_s21_exp) {
  double step = -RANGE + RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(exp(step), s21_exp(step), S21_PRECISION);
}
END_TEST

Suite *s21_exp_suite(void) {
  Suite *s = suite_create("s21_exp");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_exp);
  tcase_add_test(tc_corner, inf_check_s21_exp);
  tcase_add_test(tc_corner, nan_check_s21_exp);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_exp, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);

  return s;
}