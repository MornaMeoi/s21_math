#include "check_s21_floor.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "../check_s21_math.h"
#include "../s21_math.h"
#include "check_s21_ceil.h"

START_TEST(zero_check_s21_floor) {
  ck_assert_int_eq(floor(0.0000000), s21_floor(0.0000000));
}
END_TEST

START_TEST(left_check_s21_floor) {
  ck_assert_ldouble_eq_tol(floor(1e-10), s21_floor(1e-10), S21_PRECISION);
}
END_TEST

START_TEST(right_check_s21_floor) {
  ck_assert_ldouble_eq_tol(floor(0.9999999), s21_floor(0.9999999),
                           S21_PRECISION);
}
END_TEST

START_TEST(negative_check_s21_floor) {
  ck_assert_ldouble_eq_tol(floor(-10), s21_floor(-10), S21_PRECISION);
}
END_TEST

START_TEST(step_check_s21_floor) {
  double step = -RANGE + (double)RANGE / STEPS_AMOUNT * 2 * _i;
  ck_assert_ldouble_eq_tol(floor(step), s21_floor(step), S21_PRECISION);
}
END_TEST

Suite *s21_floor_suite() {
  Suite *s = suite_create("s21_floor");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_floor);
  tcase_add_test(tc_corner, left_check_s21_floor);
  tcase_add_test(tc_corner, right_check_s21_floor);
  tcase_add_test(tc_corner, negative_check_s21_floor);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_floor, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);
  return s;
}