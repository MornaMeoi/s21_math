#include "check_s21_sqrt.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

#define RANGE 1e5

START_TEST(negative_check_s21_sqrt) { ck_assert_ldouble_nan(s21_sqrt(-1.0)); }
END_TEST

START_TEST(zero_check_s21_sqrt) {
  ck_assert_ldouble_eq_tol(sqrt(0.0), s21_sqrt(0.0), S21_PRECISION);
}
END_TEST

START_TEST(inf_check_s21_sqrt) {
  ck_assert_ldouble_infinite(s21_sqrt(S21_INF));
}
END_TEST

START_TEST(nan_check_s21_sqrt) { ck_assert_ldouble_nan(s21_sqrt(S21_NAN)); }
END_TEST

START_TEST(step_check_s21_sqrt) {
  double step = (double)RANGE / STEPS_AMOUNT * _i;
  ck_assert_ldouble_eq_tol(sqrt(step), s21_sqrt(step), S21_PRECISION);
}
END_TEST

Suite *s21_sqrt_suite(void) {
  Suite *s = suite_create("s21_sqrt");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, negative_check_s21_sqrt);
  tcase_add_test(tc_corner, zero_check_s21_sqrt);
  tcase_add_test(tc_corner, inf_check_s21_sqrt);
  tcase_add_test(tc_corner, nan_check_s21_sqrt);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_sqrt, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);

  return s;
}