#include "s21_math.h"

long double s21_fabs(double x) { return x < 0 ? -x : x; }

int s21_abs(int x) { return s21_fabs(x); }

long double s21_ceil(double x) {
  return x == (int)x ? (int)x : (x < 0 ? (int)x : (int)(x + 1));
}

long double s21_floor(double x) {
  return x == (int)x ? (int)x : (x < 0 ? (int)(x - 1) : (int)x);
}

long double s21_fmod(double x, double y) {
  long double result = s21_fabs(x) - s21_fabs(y) * s21_floor(s21_fabs(x / y));
  if (x < 0) result = -result;
  return y == 0 ? -S21_NAN : result;
}

int IsNan(double x) { return (x >= 0) == (x < 0); }

long double s21_exp(double x) {
  long double result = 1.0;
  if (x == S21_INF)
    result = S21_INF;
  else if (IsNan(x))
    result = S21_NAN;
  else if (x != 0)
    for (double i = 1, temp_denominator = 1, temp_numerator = x;
         s21_fabs(temp_numerator / temp_denominator -
                  (temp_numerator * x) / (temp_denominator * i)) >
             S21_PRECISION / 1e4 ||
         (temp_numerator / temp_denominator > S21_PRECISION / 1e4);
         ++i, temp_denominator *= i, temp_numerator *= x)
      result += temp_numerator / temp_denominator;
  return result;
}

long double s21_log(double x) {
  long double result = 0;
  if (x == 0)
    result = -S21_INF;
  else if (x == S21_INF)
    result = S21_INF;
  else if (x < 0 || IsNan(x) || x == -S21_INF)
    result = S21_NAN;
  else if (x != 1) {
    for (; x >= 2; x /= S21_E) result += 1;
    long double temp = 0;
    for (long double i = 1, temp_numerator = x - 1;
         s21_fabs(s21_fabs(temp_numerator / i) -
                  s21_fabs(temp_numerator * (1 - x) / (i + 1))) >
             S21_PRECISION / 1e12 ||
         (temp_numerator / i > S21_PRECISION / 1e12);
         ++i, temp_numerator *= 1 - x)
      temp += temp_numerator / i;
    result += temp;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 1;
  if (base < 0 && exp != (int)exp)
    result = -S21_NAN;
  else if (base == 0 && exp < 0)
    result = S21_INF;
  else if (base == 0 && exp != 0)
    result = 0;
  else if (base != 0 && exp != 0) {
    int sign = base < 0 ? -1 : 1;
    result = s21_exp(exp * s21_log(base * sign));
    if (s21_fmod(exp, 2)) result *= sign;
  }
  return result;
}

long double s21_sqrt(double x) {
  long double result = 0;
  if (x < 0)
    result = -S21_NAN;
  else if (x == S21_E || x == 0)
    result = x;
  else if (IsNan(x))
    result = S21_NAN;
  else
    result = s21_pow(x, 0.5);
  return result;
}

long double s21_sin(double x) {
  long double result = 0;
  if (x == S21_INF || IsNan(x))
    result = S21_NAN;
  else if (x != 0) {
    x = s21_fmod(x, 2 * S21_PI);
    for (long double i = 1, temp_numerator = x, temp_denominator = 1;
         (temp_numerator / temp_denominator > S21_PRECISION / 1e12) ||
         s21_fabs(s21_fabs(temp_numerator / temp_denominator) -
                  s21_fabs(temp_numerator * x * x * (-1) /
                           (temp_denominator * (i + 1) * (i + 2)))) >
             S21_PRECISION / 1e12;
         temp_denominator *= (i + 1) * (i + 2), i += 2,
                     temp_numerator *= x * x * (-1))
      result += temp_numerator / temp_denominator;
  }
  return result;
}

long double s21_cos(double x) {
  long double result = 1;
  if (x == S21_INF || IsNan(x))
    result = S21_NAN;
  else if (x != 0) {
    x = s21_fmod(x, 2 * S21_PI);
    for (long double i = 2, temp_numerator = -x * x, temp_denominator = 2;
         (temp_numerator / temp_denominator > S21_PRECISION / 1e12) ||
         s21_fabs(s21_fabs(temp_numerator / temp_denominator) -
                  s21_fabs(temp_numerator * x * x * (-1) /
                           (temp_denominator * (i + 1) * (i + 2)))) >
             S21_PRECISION / 1e12;
         temp_denominator *= (i + 1) * (i + 2), i += 2,
                     temp_numerator *= x * x * (-1))
      result += temp_numerator / temp_denominator;
  }
  return result;
}

long double s21_tan(double x) {
  long double result = 0;
  if (x == S21_INF || IsNan(x))
    result = S21_NAN;
  else if (s21_fabs(x - S21_PI / 2) < S21_PRECISION)
    result = S21_INF;
  else if (x != 0)
    result = s21_sin(x) / s21_cos(x);
  return result;
}

long double s21_asin(double x) {
  long double result = 0;
  if (x < -1.0 || x > 1.0 || IsNan(x))
    result = S21_NAN;
  else if (x == -1 || x == 1)
    result = x * S21_PI / 2;
  else if (x != 0)
    for (long double i = 1, temp_numerator = x, temp_denominator = 1;
         (temp_numerator / temp_denominator > S21_PRECISION / 1e8) ||
         s21_fabs(s21_fabs(temp_numerator / temp_denominator) -
                  s21_fabs(temp_numerator * x * x /
                           (temp_denominator * (i + 1) * (i + 2) / i / i))) >
             S21_PRECISION / 1e8;
         i += 2, temp_numerator *= x * x,
                     temp_denominator =
                         temp_denominator * (i - 1) * i / (i - 2) / (i - 2))
      result += temp_numerator / temp_denominator;
  return result;
}

long double s21_acos(double x) {
  long double result = 0;
  if (x != 1) result = S21_PI / 2 - s21_asin(x);
  return result;
}

long double s21_atan(double x) {
  long double result = 0;
  if (IsNan(x))
    result = x;
  else if (x == S21_INF)
    result = S21_PI / 2;
  else if (x == -S21_INF)
    result = -S21_PI / 2;
  else if (x == 0)
    result = 0;
  else if (x != 0)
    result = s21_asin(x / s21_sqrt(1 + x * x));
  return result;
}