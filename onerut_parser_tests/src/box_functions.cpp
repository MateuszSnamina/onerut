#include<gtest/gtest.h>
#include<onerut_parser_tests/box_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(box_functions, re_cx_overload_1) {
    BASIC_ONERUT_TEST(sin(-.45), re_sin(-.45));
    BASIC_ONERUT_TEST(sin(-.45 + 0i), cx_sin(-.45));
    ONERUT_TEST(sin(-.45));
}

TEST(box_functions, re_cx_overload_2) {
    BASIC_ONERUT_TEST(asin(-.45), re_asin(-.45));
    BASIC_ONERUT_TEST(asin(-.45 + 0i), cx_asin(-.45));
    ONERUT_TEST(asin(-.45));
}

TEST(box_functions, re_cx_overload_3) {
    BASIC_ONERUT_TEST(sqrt(-.45), re_sqrt(-.45));
    BASIC_ONERUT_TEST(sqrt(-.45 + 0i), cx_sqrt(-.45));
    ONERUT_TEST(sqrt(-.45));
}

TEST(box_functions, re_cx_overload_4) {
    BASIC_ONERUT_TEST(sqrt(+.45), re_sqrt(+.45));
    BASIC_ONERUT_TEST(sqrt(+.45 + 0i), cx_sqrt(+.45));
    ONERUT_TEST(sqrt(+.45));
}

TEST(box_functions, re_cx_overload_5) {
    // EXTREME !!
    // TODO
    /*
    std::cout << std::setprecision(18) << std::endl;
    std::cout << std::cbrt(.45) << std::endl;
    std::cout << cbrt(.45) << std::endl;
    using TTT = double(*)(double);
    TTT fp = static_cast<TTT> (std::cbrt);
    std::cout << fp(.45) << std::endl;
    BASIC_ONERUT_TEST(.45, .45);
    BASIC_ONERUT_TEST(static_cast<double> (std::cbrt(.45)), cbrt(.45));
    //ONERUT_TEST(cbrt(-.45));
     */
}

TEST(box_functions, re_cx_overload_6) {
    BASIC_ONERUT_TEST(pow(2, 5), re_pow(2, 5));
    BASIC_ONERUT_TEST(pow(2. + 0i, 5. + 0i), cx_pow(2, 5));
    ONERUT_TEST(pow(2, 5));
}

TEST(box_functions, re_cx_overload_7) {
    BASIC_ONERUT_TEST(pow(2, 5.7), re_pow(2, 5.7));
    BASIC_ONERUT_TEST(pow(2. + 0i, 5.7 + 0i), cx_pow(2, 5.7));
    ONERUT_TEST(pow(2, 5.7));
}

TEST(box_functions, re_cx_overload_8) {
    BASIC_ONERUT_TEST(pow(2.7, 5), re_pow(2.7, 5));
    BASIC_ONERUT_TEST(pow(2.7 + 0i, 5. + 0i), cx_pow(2.7, 5));
    ONERUT_TEST(pow(2.7, 5));
}

TEST(box_functions, re_cx_overload_9) {
    BASIC_ONERUT_TEST(pow(2.7, 5.7), re_pow(2.7, 5.7));
    BASIC_ONERUT_TEST(pow(2.7 + 0i, 5.7 + 0i), cx_pow(2.7, 5.7));
    ONERUT_TEST(pow(2.7, 5.7));
}

TEST(box_functions, re_cx_overload_10) {
    BASIC_ONERUT_TEST(exp(-.45), re_exp(-.45));
    BASIC_ONERUT_TEST(exp(-.45 + 0i), cx_exp(-.45));
    ONERUT_TEST(exp(-.45));
}

TEST(box_functions, re_cx_overload_11) {
    BASIC_ONERUT_TEST(log(-.45), re_log(-.45));
    BASIC_ONERUT_TEST(log(-.45 + 0i), cx_log(-.45));
    ONERUT_TEST(log(-.45));
}

TEST(box_functions, re_cx_overload_12) {
    BASIC_ONERUT_TEST(log(.45), re_log(.45));
    BASIC_ONERUT_TEST(log(.45 + 0i), cx_log(.45));
    ONERUT_TEST(log(.45));
}

TEST(box_functions, re_cx_overload_13) {
    BASIC_ONERUT_TEST(log10(.45), re_log10(.45));
    BASIC_ONERUT_TEST(log10(.45 + 0i), cx_log10(.45));
    ONERUT_TEST(log10(.45));
}

TEST(box_functions, re_1) {
    ONERUT_TEST(expm1(2));
    ONERUT_TEST(expm1(2.7));
}

TEST(box_functions, cx_1) {
    ONERUT_TEST(real(2.7));
    ONERUT_TEST(real(2.7 + 3i));
}

TEST(box_functions, cx_2) {
    ONERUT_TEST(imag(2.7));
    ONERUT_TEST(imag(2.7 + 3i));
}

TEST(box_functions, cx_3) {
    ONERUT_TEST(conj(2.7));
    ONERUT_TEST(conj(2.7 + 3i));
}

TEST(box_functions, cx_4) {
    ONERUT_TEST(abs(2.7));
    ONERUT_TEST(abs(2.7 + 3i));
}
