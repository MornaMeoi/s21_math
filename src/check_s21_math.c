#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"
#include "tests/check_s21_abs.h"
#include "tests/check_s21_acos.h"
#include "tests/check_s21_asin.h"
#include "tests/check_s21_atan.h"
#include "tests/check_s21_ceil.h"
#include "tests/check_s21_cos.h"
#include "tests/check_s21_exp.h"
#include "tests/check_s21_fabs.h"
#include "tests/check_s21_floor.h"
#include "tests/check_s21_fmod.h"
#include "tests/check_s21_log.h"
#include "tests/check_s21_pow.h"
#include "tests/check_s21_sin.h"
#include "tests/check_s21_sqrt.h"
#include "tests/check_s21_tan.h"

int main() {
  int number_failed = 0;
  SRunner *sr;

  sr = srunner_create(s21_abs_suite());
  srunner_add_suite(sr, s21_fabs_suite());
  srunner_add_suite(sr, s21_ceil_suite());
  srunner_add_suite(sr, s21_floor_suite());
  srunner_add_suite(sr, s21_fmod_suite());
  srunner_add_suite(sr, s21_exp_suite());
  srunner_add_suite(sr, s21_log_suite());
  srunner_add_suite(sr, s21_pow_suite());
  srunner_add_suite(sr, s21_sqrt_suite());
  srunner_add_suite(sr, s21_sin_suite());
  srunner_add_suite(sr, s21_cos_suite());
  srunner_add_suite(sr, s21_tan_suite());
  srunner_add_suite(sr, s21_asin_suite());
  srunner_add_suite(sr, s21_acos_suite());
  srunner_add_suite(sr, s21_atan_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}