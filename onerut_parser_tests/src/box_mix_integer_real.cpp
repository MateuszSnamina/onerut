#include<gtest/gtest.h>
#include<onerut_parser_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(box_mix_integer_real, op_plus_munis_1) {
    ONERUT_TEST(540 + 7.8);
}

TEST(box_mix_integer_real, op_plus_munis_2) {
    ONERUT_TEST(540.5 + 7);
}

TEST(box_mix_integer_real, op_plus_munis_3) {
    ONERUT_TEST(540 - 75.8);
}

TEST(box_mix_integer_real, op_plus_munis_4) {
    ONERUT_TEST(540.5 - 75);
}

TEST(box_mix_integer_real, op_plus_munis_5) {
    ONERUT_TEST(540 + 75 + 764.3);
}

TEST(box_mix_integer_real, op_plus_munis_6) {
    ONERUT_TEST(540.5 + 75 + 764.3);
}

TEST(box_mix_integer_real, op_plus_munis_7) {
    ONERUT_TEST(540.5 - 75 + 764);
}

TEST(box_mix_integer_real, op_plus_munis_8) {
    ONERUT_TEST(-540 - 75.8 + 764);
}

TEST(box_mix_integer_real, op_prod_div_1) {
    ONERUT_TEST(540 * 75.8);
}

TEST(box_mix_integer_real, op_prod_div_2) {
    ONERUT_TEST(540.5 * 75);
}

TEST(box_mix_integer_real, op_prod_div_3) {
    ONERUT_TEST(540 / 75.8);
}

TEST(box_mix_integer_real, op_prod_div_4) {
    ONERUT_TEST(+540.5 / 75);
}

TEST(box_mix_integer_real, op_prod_div_5) {
    ONERUT_TEST(540 * 75 * 764.3);
}

TEST(box_mix_integer_real, op_prod_div_6) {
    ONERUT_TEST(540 * 75.8 * 764.3);
}

TEST(box_mix_integer_real, op_plus_minus_prod_div_1) {
    ONERUT_TEST(-540.5 - 75 / 764);
}

TEST(box_mix_integer_real, op_plus_minus_10) {
    BASIC_ONERUT_TEST(10000000000000000l + 1., 10000000000000000 + 1.);
}

TEST(box_mix_integer_real, op_plus_minus_prod_div_grouping_8) {
    ONERUT_TEST((-54 - 75.8) * 764.3);
}

TEST(box_mix_integer_real, op_plus_minus_prod_div_grouping_9) {
    ONERUT_TEST(-54 - (75.8 * 764.3));
}

TEST(box_mix_integer_real, op_plus_minus_prod_div_grouping_10) {
    ONERUT_TEST(-54 / (75.8 + 764.3));
}