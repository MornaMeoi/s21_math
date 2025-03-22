#include "check_s21_tan.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

#define RANGE 1e3

START_TEST(zero_check_s21_tan) {
  ck_assert_ldouble_eq_tol(tan(0.0), s21_tan(0.0), S21_PRECISION);
}
END_TEST

START_TEST(inf_check_s21_tan) { ck_assert_ldouble_nan(s21_tan(S21_INF)); }
END_TEST

START_TEST(nan_check_s21_tan) { ck_assert_ldouble_nan(s21_tan(S21_NAN)); }
END_TEST

START_TEST(half_pi_check_s21_tan) {
  ck_assert_ldouble_infinite(s21_tan(S21_PI / 2));
}
END_TEST

START_TEST(step_check_s21_tan) {
  double step = RANGE + (double)RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(tan(step), s21_tan(step), S21_PRECISION);
}
END_TEST

Suite *s21_tan_suite(void) {
  Suite *s = suite_create("s21_tan");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_tan);
  tcase_add_test(tc_corner, inf_check_s21_tan);
  tcase_add_test(tc_corner, nan_check_s21_tan);
  tcase_add_test(tc_corner, half_pi_check_s21_tan);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_tan, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);

  return s;
}