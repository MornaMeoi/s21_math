#include "check_s21_abs.h"

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "../check_s21_math.h"
#include "../s21_math.h"

START_TEST(zero_check_s21_abs) { ck_assert_int_eq(abs(0), s21_abs(0)); }
END_TEST

START_TEST(step_check_s21_abs) {
  int step = INT_MIN + (int)(UINT_MAX / STEPS_AMOUNT) * _i;
  ck_assert_int_eq(abs(step), s21_abs(step));
}
END_TEST

Suite *s21_abs_suite() {
  Suite *s = suite_create("s21_abs");
  TCase *tc_corner = tcase_create("corner"), *tc_step = tcase_create("step");

  tcase_add_test(tc_corner, zero_check_s21_abs);
  suite_add_tcase(s, tc_corner);

  tcase_add_loop_test(tc_step, step_check_s21_abs, 0, STEPS_AMOUNT);
  suite_add_tcase(s, tc_step);
  return s;
}