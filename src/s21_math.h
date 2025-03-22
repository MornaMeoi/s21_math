#ifndef S21_MATH_H
#define S21_MATH_H

#define S21_PRECISION 1e-6
#define S21_E 2.71828182845904L
#define S21_PI 3.14159265358979323846264L
#define S21_INF __builtin_inf()
#define S21_NAN __builtin_nan("")
#define S21_POW_CONST 0x5f3759df

int IsNan(double x);
int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

#endif