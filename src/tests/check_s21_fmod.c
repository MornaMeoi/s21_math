#include "check_s21_fmod.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

#define CONST 1234.567

START_TEST(zero_check_s21_fmod) { ck_assert_ldouble_nan(s21_fmod(2.28, 0.0)); }
END_TEST

START_TEST(negative_numerator_check_s21_fmod) {
  ck_assert_ldouble_eq_tol(fmod(-5.2, 3.3), s21_fmod(-5.2, 3.3), S21_PRECISION);
}
END_TEST

START_TEST(negative_denominator_check_s21_fmod) {
  ck_assert_ldouble_eq_tol(fmod(5.2, -3.3), s21_fmod(5.2, -3.3), S21_PRECISION);
}
END_TEST

START_TEST(negative_check_s21_fmod) {
  ck_assert_ldouble_eq_tol(fmod(-5.2, -3.3), s21_fmod(-5.2, -3.3),
                           S21_PRECISION);
}
END_TEST

START_TEST(numerator_step_check_s21_fmod) {
  double step = INT_MIN + (double)UINT_MAX / STEPS_AMOUNT * _i;
  ck_assert_ldouble_eq_tol(fmod(step, CONST), s21_fmod(step, CONST),
                           S21_PRECISION);
}
END_TEST

START_TEST(denominator_step_check_s21_fmod) {
  double step = INT_MIN + (double)UINT_MAX / STEPS_AMOUNT * _i;
  ck_assert_ldouble_eq_tol(fmod(CONST, step), s21_fmod(CONST, step),
                           S21_PRECISION);
}
END_TEST

Suite *s21_fmod_suite() {
  Suite *s = suite_create("s21_fmod");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_fmod);
  tcase_add_test(tc_corner, negative_numerator_check_s21_fmod);
  tcase_add_test(tc_corner, negative_denominator_check_s21_fmod);
  tcase_add_test(tc_corner, negative_check_s21_fmod);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, numerator_step_check_s21_fmod, 0, STEPS_AMOUNT);
  tcase_add_loop_test(tc_step, denominator_step_check_s21_fmod, 0,
                      STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);

  return s;
}