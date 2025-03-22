#include "check_s21_atan.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

#define RANGE 53

START_TEST(zero_check_s21_atan) {
  ck_assert_ldouble_eq_tol(atan(0.0), s21_atan(0.0), S21_PRECISION);
}
END_TEST

START_TEST(one_check_s21_atan) {
  ck_assert_ldouble_eq_tol(atan(1.0), s21_atan(1.0), S21_PRECISION);
}
END_TEST

START_TEST(inf_check_s21_atan) {
  ck_assert_ldouble_eq_tol(atan(S21_INF), s21_atan(S21_INF), S21_PRECISION);
}
END_TEST

START_TEST(neg_inf_check_s21_atan) {
  ck_assert_ldouble_eq_tol(atan(-S21_INF), s21_atan(-S21_INF), S21_PRECISION);
}
END_TEST

START_TEST(nan_check_s21_atan) { ck_assert_ldouble_nan(s21_atan(S21_NAN)); }
END_TEST

START_TEST(step_check_s21_atan) {
  double step = -RANGE + (double)RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(atan(step), s21_atan(step), S21_PRECISION);
}
END_TEST

Suite *s21_atan_suite(void) {
  Suite *s = suite_create("s21_atan");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_atan);
  tcase_add_test(tc_corner, one_check_s21_atan);
  tcase_add_test(tc_corner, inf_check_s21_atan);
  tcase_add_test(tc_corner, neg_inf_check_s21_atan);
  tcase_add_test(tc_corner, nan_check_s21_atan);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_atan, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);

  return s;
}