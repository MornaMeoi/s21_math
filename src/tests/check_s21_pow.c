#include "check_s21_pow.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

#define NEGATIVE_NUMERATOR -5
#define CONST 3
#define RANGE 12

START_TEST(negative_and_not_int_check_s21_pow) {
  ck_assert_ldouble_nan(s21_pow(-2.5, 1.5));
}
END_TEST

START_TEST(zero_and_zero_check_s21_pow) {
  ck_assert_ldouble_eq_tol(pow(0.0, 0.0), s21_pow(0.0, 0.0), S21_PRECISION);
}
END_TEST

START_TEST(zero_and_negative_check_s21_pow) {
  ck_assert_ldouble_infinite(s21_pow(0.0, -1.0));
}
END_TEST

START_TEST(number_and_zero_check_s21_pow) {
  ck_assert_ldouble_eq_tol(pow(5.0, 0.0), s21_pow(5.0, 0.0), S21_PRECISION);
}
END_TEST

START_TEST(negative_base_step_check_s21_pow) {
  double step = -RANGE + _i;
  ck_assert_ldouble_eq_tol(pow(NEGATIVE_NUMERATOR, step),
                           s21_pow(NEGATIVE_NUMERATOR, step), S21_PRECISION);
}
END_TEST

START_TEST(base_step_check_s21_pow) {
  double step = -RANGE + (double)RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(pow(step, CONST), s21_pow(step, CONST),
                           S21_PRECISION);
}
END_TEST

START_TEST(power_step_check_s21_pow) {
  double step = -RANGE + (double)RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(pow(CONST, step), s21_pow(CONST, step),
                           S21_PRECISION);
}
END_TEST

Suite *s21_pow_suite(void) {
  Suite *s = suite_create("s21_pow");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, negative_and_not_int_check_s21_pow);
  tcase_add_test(tc_corner, zero_and_zero_check_s21_pow);
  tcase_add_test(tc_corner, zero_and_negative_check_s21_pow);
  tcase_add_test(tc_corner, number_and_zero_check_s21_pow);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, negative_base_step_check_s21_pow, 0, 2 * RANGE);
  tcase_add_loop_test(tc_step, base_step_check_s21_pow, 0, STEPS_AMOUNT);
  tcase_add_loop_test(tc_step, power_step_check_s21_pow, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);

  return s;
}