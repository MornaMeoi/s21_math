#include "check_s21_asin.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

#define RANGE 1

START_TEST(left_check_s21_asin) { ck_assert_ldouble_nan(s21_asin(-1.5)); }
END_TEST

START_TEST(right_check_s21_asin) { ck_assert_ldouble_nan(s21_asin(1.5)); }
END_TEST

START_TEST(nan_check_s21_asin) { ck_assert_ldouble_nan(s21_asin(S21_NAN)); }
END_TEST

START_TEST(zero_check_s21_asin) {
  ck_assert_ldouble_eq_tol(asin(0.0), s21_asin(0.0), S21_PRECISION);
}
END_TEST

START_TEST(negative_one_check_s21_asin) {
  ck_assert_ldouble_eq_tol(asin(-1.0), s21_asin(-1.0), S21_PRECISION);
}
END_TEST

START_TEST(one_check_s21_asin) {
  ck_assert_ldouble_eq_tol(asin(1.0), s21_asin(1.0), S21_PRECISION);
}
END_TEST

START_TEST(step_check_s21_asin) {
  double step = -RANGE + (double)RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(asin(step), s21_asin(step), S21_PRECISION);
}
END_TEST

Suite *s21_asin_suite(void) {
  Suite *s = suite_create("s21_asin");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, left_check_s21_asin);
  tcase_add_test(tc_corner, right_check_s21_asin);
  tcase_add_test(tc_corner, nan_check_s21_asin);
  tcase_add_test(tc_corner, zero_check_s21_asin);
  tcase_add_test(tc_corner, negative_one_check_s21_asin);
  tcase_add_test(tc_corner, one_check_s21_asin);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_asin, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);

  return s;
}