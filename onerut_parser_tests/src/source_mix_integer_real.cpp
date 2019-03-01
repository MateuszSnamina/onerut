#include<gtest/gtest.h>
#include<onerut_parser_tests/source_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(source_mix_integer_real, op_plus_munis_1) {
    onerut_source_test("OpPlusMinus(+,LitLong(540),LitDouble(7.800000))", "540 + 7.8");
}

TEST(source_mix_integer_real, op_plus_munis_2) {
    onerut_source_test("OpPlusMinus(+,LitDouble(540.500000),LitLong(7))", "540.5 + 7");
}

TEST(source_mix_integer_real, op_plus_munis_3) {
    onerut_source_test("OpPlusMinus(-,LitLong(540),LitDouble(75.800000))", "540 - 75.8");
}

TEST(source_mix_integer_real, op_plus_munis_4) {
    onerut_source_test("OpPlusMinus(-,LitDouble(540.500000),LitLong(75))", "540.5 - 75");
}

TEST(source_mix_integer_real, op_plus_munis_5) {
    onerut_source_test("OpPlusMinus(++,LitLong(540),LitLong(75),LitDouble(764.300000))", "540 + 75 + 764.3");
}

TEST(source_mix_integer_real, op_plus_munis_6) {
    onerut_source_test("OpPlusMinus(++,LitDouble(540.500000),LitLong(75),LitDouble(764.300000))", "540.5 + 75 + 764.3");
}

TEST(source_mix_integer_real, op_plus_munis_7) {
    onerut_source_test("OpPlusMinus(-+,LitDouble(540.500000),LitLong(75),LitLong(764))", "540.5 - 75 + 764");
}

TEST(source_mix_integer_real, op_plus_munis_8) {
    onerut_source_test("OpPlusMinus(-+,LitLong(-540),LitDouble(75.800000),LitLong(764))", "-540 - 75.8 + 764");
}

TEST(source_mix_integer_real, op_prod_div_1) {
    onerut_source_test("OpProdDiv(*,LitLong(540),LitDouble(75.800000))", "540 * 75.8");
}

TEST(source_mix_integer_real, op_prod_div_2) {
    onerut_source_test("OpProdDiv(*,LitDouble(540.500000),LitLong(75))", "540.5 * 75");
}

TEST(source_mix_integer_real, op_prod_div_3) {
    onerut_source_test("OpProdDiv(/,LitLong(540),LitDouble(75.800000))", "540 / 75.8");
}

TEST(source_mix_integer_real, op_prod_div_4) {
    onerut_source_test("OpProdDiv(/,LitDouble(540.500000),LitLong(75))", "+540.5 / 75");
}

TEST(source_mix_integer_real, op_prod_div_5) {
    onerut_source_test("OpProdDiv(**,LitLong(540),LitLong(75),LitDouble(764.300000))", "540 * 75 * 764.3");
}

TEST(source_mix_integer_real, op_prod_div_6) {
    onerut_source_test("OpProdDiv(**,LitLong(540),LitDouble(75.800000),LitDouble(764.300000))", "540 * 75.8 * 764.3");
}

TEST(source_mix_integer_real, op_plus_minus_prod_div_1) {
    onerut_source_test("OpPlusMinus(-,LitDouble(-540.500000),OpProdDiv(/,LitLong(75),LitLong(764)))", "-540.5 - 75 / 764");
}

TEST(source_mix_integer_real, op_plus_minus_10) {
    onerut_source_test("OpPlusMinus(+,LitLong(10000000000000000),LitDouble(1.000000))", "10000000000000000 + 1.");
}

TEST(source_mix_integer_real, op_plus_minus_prod_div_grouping_8) {
    onerut_source_test("OpProdDiv(*,OpPlusMinus(-,LitLong(-54),LitDouble(75.800000)),LitDouble(764.300000))", "(-54 - 75.8) * 764.3");
}

TEST(source_mix_integer_real, op_plus_minus_prod_div_grouping_9) {
    onerut_source_test("OpPlusMinus(-,LitLong(-54),OpProdDiv(*,LitDouble(75.800000),LitDouble(764.300000)))", "-54 - (75.8 * 764.3)");
}

TEST(source_mix_integer_real, op_plus_minus_prod_div_grouping_10) {
    onerut_source_test("OpProdDiv(/,LitLong(-54),OpPlusMinus(+,LitDouble(75.800000),LitDouble(764.300000)))", "-54 / (75.8 + 764.3)");
}