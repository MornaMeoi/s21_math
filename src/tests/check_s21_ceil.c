#include "check_s21_ceil.h"

#include <check.h>
#include <limits.h>
#include <math.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

START_TEST(zero_check_s21_ceil) {
  ck_assert_ldouble_eq_tol(ceil(0.0), s21_ceil(0.0), S21_PRECISION);
}
END_TEST

START_TEST(left_check_s21_ceil) {
  ck_assert_ldouble_eq_tol(ceil(1e-10), s21_ceil(1e-10), S21_PRECISION);
}
END_TEST

START_TEST(right_check_s21_ceil) {
  ck_assert_ldouble_eq_tol(ceil(0.9999999), s21_ceil(0.9999999), S21_PRECISION);
}
END_TEST

START_TEST(negative_check_s21_ceil) {
  ck_assert_ldouble_eq_tol(ceil(-10), s21_ceil(-10), S21_PRECISION);
}
END_TEST

START_TEST(step_check_s21_ceil) {
  double step = -RANGE + (double)RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(ceil(step), s21_ceil(step), S21_PRECISION);
}
END_TEST

Suite *s21_ceil_suite() {
  Suite *s = suite_create("s21_ceil");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_ceil);
  tcase_add_test(tc_corner, left_check_s21_ceil);
  tcase_add_test(tc_corner, right_check_s21_ceil);
  tcase_add_test(tc_corner, negative_check_s21_ceil);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_ceil, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);
  return s;
}