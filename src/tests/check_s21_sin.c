#include "check_s21_sin.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

#define RANGE 1e5

START_TEST(zero_check_s21_sin) {
  ck_assert_ldouble_eq_tol(sin(0.0), s21_sin(0.0), S21_PRECISION);
}
END_TEST

START_TEST(inf_check_s21_sin) { ck_assert_ldouble_nan(s21_sin(S21_INF)); }
END_TEST

START_TEST(nan_check_s21_sin) { ck_assert_ldouble_nan(s21_sin(S21_NAN)); }
END_TEST

START_TEST(step_check_s21_sin) {
  double step = RANGE + (double)RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(sin(step), s21_sin(step), S21_PRECISION);
}
END_TEST

Suite *s21_sin_suite(void) {
  Suite *s = suite_create("s21_sin");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_sin);
  tcase_add_test(tc_corner, inf_check_s21_sin);
  tcase_add_test(tc_corner, nan_check_s21_sin);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_sin, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);

  return s;
}