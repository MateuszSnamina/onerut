#include<gtest/gtest.h>
#include<onerut_parser_tests/box_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(boxFunctions, reCxOverload1) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_sin(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_sin());
    BASIC_ONERUT_BOX_VALUE_TEST(sin(-.45), re_sin(-.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, re_sin(-.45i));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_sin(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_sin());
    BASIC_ONERUT_BOX_VALUE_TEST(sin(-.45 + 0i), cx_sin(-.45));
    BASIC_ONERUT_BOX_VALUE_TEST(sin(-.45 + 1i), cx_sin(-.45 + 1i));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, sin(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, sin())
    ONERUT_BOX_VALUE_TEST(sin(-.45));
    ONERUT_BOX_VALUE_TEST(sin(-.45 + 1i));
}

TEST(boxFunctions, reCxOverload2) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_asin(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_asin());
    BASIC_ONERUT_BOX_VALUE_TEST(asin(-.45), re_asin(-.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, re_asin(-.45i))
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_asin(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_asin());
    BASIC_ONERUT_BOX_VALUE_TEST(asin(-.45 + 0i), cx_asin(-.45));
    BASIC_ONERUT_BOX_VALUE_TEST(asin(-.45 + 1i), cx_asin(-.45 + 1i));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, asin(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, asin())
    ONERUT_BOX_VALUE_TEST(asin(-.45));
    ONERUT_BOX_VALUE_TEST(asin(-.45 + 1i));
}

TEST(boxFunctions, reCxOverload3) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_sqrt(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_sqrt());
    BASIC_ONERUT_BOX_VALUE_TEST(sqrt(-.45), re_sqrt(-.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, re_sqrt(-.45i))
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_sqrt(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_sqrt());
    BASIC_ONERUT_BOX_VALUE_TEST(sqrt(-.45 + 0i), cx_sqrt(-.45));
    BASIC_ONERUT_BOX_VALUE_TEST(sqrt(-.45 + 1i), cx_sqrt(-.45 + 1i));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, sqrt(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, sqrt())
    ONERUT_BOX_VALUE_TEST(sqrt(-.45));
    ONERUT_BOX_VALUE_TEST(sqrt(-.45 + 1i));
}

TEST(boxFunctions, reCxOverload4) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_sqrt(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_sqrt());
    BASIC_ONERUT_BOX_VALUE_TEST(sqrt(.45), re_sqrt(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, re_sqrt(.45i))
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_sqrt(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_sqrt());
    BASIC_ONERUT_BOX_VALUE_TEST(sqrt(.45 + 0i), cx_sqrt(.45));
    BASIC_ONERUT_BOX_VALUE_TEST(sqrt(.45 + 1i), cx_sqrt(.45 + 1i));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, sqrt(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, sqrt())
    ONERUT_BOX_VALUE_TEST(sqrt(.45));
    ONERUT_BOX_VALUE_TEST(sqrt(.45 + 1i));
}

TEST(boxFunctions, reCxOverload5) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_abs(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_abs());
    BASIC_ONERUT_BOX_VALUE_TEST(fabs(.45), re_abs(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, re_abs(.45i))
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_abs(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_abs());
    BASIC_ONERUT_BOX_VALUE_TEST(fabs(.45 + 0i), cx_abs(.45));
    BASIC_ONERUT_BOX_VALUE_TEST(abs(.45 + 1i), cx_abs(.45 + 1i));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, abs(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, abs())
    BASIC_ONERUT_BOX_VALUE_TEST(fabs(.45), abs(.45));
    BASIC_ONERUT_BOX_VALUE_TEST(abs(.45 + 1i), abs(.45 + 1i));
}

TEST(boxFunctions, reCxOverload6) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_pow(1));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_pow(1, 2, 3));
    BASIC_ONERUT_BOX_VALUE_TEST(pow(2, 5), re_pow(2, 5));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, re_pow(.45i, 2));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_pow());
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_pow(1, 2, 3));
    BASIC_ONERUT_BOX_VALUE_TEST(pow(2. + 0i, 5. + 0i), cx_pow(2, 5));
    BASIC_ONERUT_BOX_VALUE_TEST(pow(2. + 1i, 5. + 0i), cx_pow(2 + 1i, 5));
    BASIC_ONERUT_BOX_VALUE_TEST(pow(2. + 0i, 5. + 1i), cx_pow(2, 5 + 1i));
    BASIC_ONERUT_BOX_VALUE_TEST(pow(2. + 1i, 5. + 1i), cx_pow(2 + 1i, 5 + 1i));
    //    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, pow(1));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, pow(1, 2, 3))
    ONERUT_BOX_VALUE_TEST(pow(2, 5));
    ONERUT_BOX_VALUE_TEST(pow(2. + 1i, 5));
    ONERUT_BOX_VALUE_TEST(pow(2, 5. + 1i));
    ONERUT_BOX_VALUE_TEST(pow(2. + 1i, 5. + 1i));
}

TEST(boxFunctions, reCxOverload7) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_exp(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_exp());
    BASIC_ONERUT_BOX_VALUE_TEST(exp(.45), re_exp(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, re_exp(.45i))
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_exp(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_exp());
    BASIC_ONERUT_BOX_VALUE_TEST(exp(.45 + 0i), cx_exp(.45));
    BASIC_ONERUT_BOX_VALUE_TEST(exp(.45 + 1i), cx_exp(.45 + 1i));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, exp(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, exp())
    ONERUT_BOX_VALUE_TEST(exp(.45));
    ONERUT_BOX_VALUE_TEST(exp(.45 + 1i));
}

TEST(boxFunctions, reCxOverload8) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_log(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_log());
    BASIC_ONERUT_BOX_VALUE_TEST(log(.45), re_log(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, re_log(.45i))
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_log(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_log());
    BASIC_ONERUT_BOX_VALUE_TEST(log(.45 + 0i), cx_log(.45));
    BASIC_ONERUT_BOX_VALUE_TEST(log(.45 + 1i), cx_log(.45 + 1i));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, log(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, log())
    ONERUT_BOX_VALUE_TEST(log(.45));
    ONERUT_BOX_VALUE_TEST(log(.45 + 1i));
}

TEST(boxFunctions, reCxOverload9) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_log10(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, re_log10());
    BASIC_ONERUT_BOX_VALUE_TEST(log10(.45), re_log10(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, re_log10(.45i))
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_log10(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cx_log10());
    BASIC_ONERUT_BOX_VALUE_TEST(log10(.45 + 0i), cx_log10(.45));
    BASIC_ONERUT_BOX_VALUE_TEST(log10(.45 + 1i), cx_log10(.45 + 1i));
    // ----
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, log10(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, log10())
    ONERUT_BOX_VALUE_TEST(log10(.45));
    ONERUT_BOX_VALUE_TEST(log10(.45 + 1i));
}

TEST(boxFunctions, re1) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cbrt(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cbrt())
    ONERUT_BOX_VALUE_TEST(cbrt(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, cbrt(.45i))
}

TEST(boxFunctions, re2) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, expm1(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, expm1())
    ONERUT_BOX_VALUE_TEST(expm1(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, expm1(.45i))
}

TEST(boxFunctions, re3) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, log2(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, log2())
    ONERUT_BOX_VALUE_TEST(log2(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, log2(.45i))
}

TEST(boxFunctions, re4) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, log1p(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, log1p())
    ONERUT_BOX_VALUE_TEST(log1p(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, log1p(.45i))
}

TEST(boxFunctions, re5) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, erf(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, erf())
    ONERUT_BOX_VALUE_TEST(erf(.45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, erf(.45i))
}

TEST(boxFunctions, re6) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, hypot(1));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, hypot(1, 2, 3))
    ONERUT_BOX_VALUE_TEST(hypot(.45, .75));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, hypot(.45i, .75))
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, hypot(.45, .75i))
}

TEST(boxFunctions, cx1) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, real(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, real())
    ONERUT_BOX_VALUE_TEST(real(.45));
    ONERUT_BOX_VALUE_TEST(real(.45 + 2i));
}

TEST(boxFunctions, cx2) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, imag(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, imag())
    ONERUT_BOX_VALUE_TEST(imag(.45));
    ONERUT_BOX_VALUE_TEST(imag(.45 + 2i));
}

TEST(boxFunctions, cx3) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, conj(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, conj())
    ONERUT_BOX_VALUE_TEST(conj(.45));
    ONERUT_BOX_VALUE_TEST(conj(.45 + 2i));
}

TEST(boxFunctions, cx4) {
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, norm(1, 2));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, norm())
    ONERUT_BOX_VALUE_TEST(norm(.45));
    ONERUT_BOX_VALUE_TEST(norm(.45 + 2i));
}