#include<gtest/gtest.h>
#include<onerut_parser_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(pure_real, literal_1) {
    ONERUT_TEST(6445.);
}

TEST(pure_real, literal_2) {
    ONERUT_TEST(6445.0);
}

TEST(pure_real, literal_3) {
    ONERUT_TEST(.6445);
}

TEST(pure_real, literal_4) {
    ONERUT_TEST(0.6445);
}

TEST(pure_real, literal_5) {
    ONERUT_TEST(1e5);
}

TEST(pure_real, literal_6) {
    ONERUT_TEST(1e+5);
}

TEST(pure_real, literal_7) {
    ONERUT_TEST(+1e-5);
}

TEST(pure_real, literal_8) {
    ONERUT_TEST(inf);
}

TEST(pure_real, literal_9) {
    ONERUT_TEST(-6445.);
}

TEST(pure_real, literal_10) {
    ONERUT_TEST(-.6445);
}

TEST(pure_real, literal_11) {
    ONERUT_TEST(-inf);
}

TEST(pure_real, op_plus_munis_1) {
    ONERUT_TEST(540.5 + 7.8);
}

TEST(pure_real, op_plus_munis_2) {
    ONERUT_TEST(540.5 - 75.8);
}

TEST(pure_real, op_plus_munis_3) {
    ONERUT_TEST(+540.5 - 75.8);
}

TEST(pure_real, op_plus_munis_4) {
    ONERUT_TEST(-540.5 + 75.8);
}

TEST(pure_real, op_plus_munis_5) {
    ONERUT_TEST(540.5 + 75.8 + 764.3);
}

TEST(pure_real, op_plus_munis_6) {
    ONERUT_TEST(540.5 + 75.8 + 764.3);
}

TEST(pure_real, op_plus_munis_7) {
    ONERUT_TEST(540.5 - 75.8 + 764.3);
}

TEST(pure_real, op_plus_munis_8) {
    ONERUT_TEST(-540.5 - 75.8 + 764.3);
}

TEST(pure_real, op_plus_munis_9) {
    ONERUT_TEST(-540.5 - 75.8 - 764.3);
}

TEST(pure_real, op_plus_minus_10) {
    BASIC_ONERUT_TEST(10000000000000000. + 1., 10000000000000000. + 1.);
}

TEST(pure_real, op_prod_div_1) {
    ONERUT_TEST(540.5 * 75.8);
}

TEST(pure_real, op_prod_div_2) {
    ONERUT_TEST(540.5 / 75.8);
}

TEST(pure_real, op_prod_div_3) {
    ONERUT_TEST(+540.5 / 75.8);
}

TEST(pure_real, op_prod_div_4) {
    ONERUT_TEST(-540.5 * 75.8);
}

TEST(pure_real, op_prod_div_5) {
    ONERUT_TEST(540.5 * 75.8 * 764.3);
}

TEST(pure_real, op_prod_div_6) {
    ONERUT_TEST(540.5 * 75.8 * 764.3);
}

TEST(pure_real, op_prod_div_7) {
    ONERUT_TEST(540.5 / 75.8 * 764.3);
}

TEST(pure_real, op_prod_div_8) {
    ONERUT_TEST(-540.5 / 75.8 / 764.3);
}

TEST(pure_real, op_plus_minus_prod_div_1) {
    ONERUT_TEST(-540.5 - 75.8 * 764.3);
}

TEST(pure_real, op_plus_minus_prod_div_2) {
    ONERUT_TEST(-540.5 * 75.8 + 764.3);
}

TEST(pure_real, op_plus_minus_prod_div_3) {
    ONERUT_TEST(-540.5 - 75.8 / 764.3);
}

TEST(pure_real, op_plus_minus_prod_div_4) {
    ONERUT_TEST(-540.5 / 75.8 + 764.3);
}

TEST(pure_real, simple_grouping_1) {
    ONERUT_TEST((450.5));
}

TEST(pure_real, simple_grouping_2) {
    ONERUT_TEST(+(450.5));
}

TEST(pure_real, simple_grouping_3) {
    ONERUT_TEST(-(450.5));
}

TEST(pure_real, simple_grouping_4) {
    ONERUT_TEST(+(-45.5));
}

TEST(pure_real, simple_grouping_5) {
    ONERUT_TEST(-(-45.5));
}

TEST(pure_real, simple_grouping_6) {
    ONERUT_TEST(-((-45.5)));
}

TEST(pure_real, simple_grouping_7) {
    BASIC_ONERUT_TEST(-((-45.5)), -([-45.5]));
}

TEST(pure_real, op_plus_minus_prod_div_grouping_1) {
    ONERUT_TEST((540.5 * 75.8 * 764.3));
}

TEST(pure_real, op_plus_minus_prod_div_grouping_2) {
    ONERUT_TEST((540.5 * 75.8) * 764.3);
}

TEST(pure_real, op_plus_minus_prod_div_grouping_4) {
    ONERUT_TEST((540.5 / 75.8) * 764.3);
}

TEST(pure_real, op_plus_minus_prod_div_grouping_5) {
    ONERUT_TEST(540.5 / (75.8 * 764.3));
}

TEST(pure_real, op_plus_minus_prod_div_grouping_6) {
    ONERUT_TEST((-540.5 / 75.8) / 764.3);
}

TEST(pure_real, op_plus_minus_prod_div_grouping_7) {
    ONERUT_TEST(-540.5 / (75.8 / 764.3));
}

TEST(pure_real, op_plus_minus_prod_div_grouping_8) {
    ONERUT_TEST((-54 - 75.8) * 764.3);
}

TEST(pure_real, op_plus_minus_prod_div_grouping_9) {
    ONERUT_TEST(-54 - (75.8 * 764.3));
}

TEST(pure_real, op_plus_minus_prod_div_grouping_10) {
    ONERUT_TEST(-54 / (75.8 + 764.3));
}

