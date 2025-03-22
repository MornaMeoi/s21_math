#include "check_s21_fabs.h"

#include <check.h>
#include <limits.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

START_TEST(zero_check_s21_fabs) {
  ck_assert_ldouble_eq_tol(fabs(0.0), s21_fabs(0.0), S21_PRECISION);
}
END_TEST

START_TEST(step_check_s21_fabs) {
  double step = INT_MIN + (double)UINT_MAX / STEPS_AMOUNT * _i;
  ck_assert_ldouble_eq_tol(fabs(step), s21_fabs(step), S21_PRECISION);
}
END_TEST

Suite *s21_fabs_suite() {
  Suite *s = suite_create("s21_fabs");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_fabs);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_fabs, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);
  return s;
}