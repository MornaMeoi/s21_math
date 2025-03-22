#include "check_s21_cos.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

#define RANGE 1e5

START_TEST(zero_check_s21_cos) {
  ck_assert_ldouble_eq_tol(cos(0.0), s21_cos(0.0), S21_PRECISION);
}
END_TEST

START_TEST(inf_check_s21_cos) { ck_assert_ldouble_nan(s21_cos(S21_INF)); }
END_TEST

START_TEST(nan_check_s21_cos) { ck_assert_ldouble_nan(s21_cos(S21_NAN)); }
END_TEST

START_TEST(step_check_s21_cos) {
  double step = RANGE + (double)RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(cos(step), s21_cos(step), S21_PRECISION);
}
END_TEST

Suite *s21_cos_suite(void) {
  Suite *s = suite_create("s21_cos");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_cos);
  tcase_add_test(tc_corner, inf_check_s21_cos);
  tcase_add_test(tc_corner, nan_check_s21_cos);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_cos, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);

  return s;
}