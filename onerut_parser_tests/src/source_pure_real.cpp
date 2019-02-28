#include<gtest/gtest.h>
#include<onerut_parser_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

// [...]

TEST(source_pure_real, op_prod_div_7) {
    onerut_source_test("OpProdDiv(/*,LitDouble(540.500000),LitDouble(75.800000),LitDouble(764.300000))", "540.5 / 75.8 * 764.3");
}

TEST(source_pure_real, op_prod_div_8) {
    onerut_source_test("OpProdDiv(//,LitDouble(-540.500000),LitDouble(75.800000),LitDouble(764.300000))", "-540.5 / 75.8 / 764.3");
}

// [...]

TEST(source_pure_real, op_plus_minus_prod_div_2) {
    onerut_source_test("OpPlusMinus(+,OpProdDiv(*,LitDouble(-540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "-540.5 * 75.8 + 764.3");
}

TEST(source_pure_real, op_plus_minus_prod_div_3) {
    onerut_source_test("OpPlusMinus(-,LitDouble(-540.500000),OpProdDiv(/,LitDouble(75.800000),LitDouble(764.300000)))", "-540.5 - 75.8 / 764.3");
}

TEST(source_pure_real, op_plus_minus_prod_div_4) {
    onerut_source_test("OpPlusMinus(+,OpProdDiv(/,LitDouble(-540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "-540.5 / 75.8 + 764.3");
}

// [...]

TEST(source_pure_real, op_plus_minus_prod_div_grouping_1) {
    onerut_source_test("OpProdDiv(**,LitDouble(540.500000),LitDouble(75.800000),LitDouble(764.300000))", "(540.5 * 75.8 * 764.3)");
}

TEST(source_pure_real, op_plus_minus_prod_div_grouping_2) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(*,LitDouble(540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "(540.5 * 75.8) * 764.3");
}

TEST(source_pure_real, op_plus_minus_prod_div_grouping_3) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(/,LitDouble(540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "(540.5 / 75.8) * 764.3");
}

TEST(source_pure_real, op_plus_minus_prod_div_grouping_4) {
    onerut_source_test("OpProdDiv(/,LitDouble(540.500000),OpProdDiv(*,LitDouble(75.800000),LitDouble(764.300000)))", "540.5 / (75.8 * 764.3)");
}

TEST(source_pure_real, op_plus_minus_prod_div_grouping_5) {
    onerut_source_test("OpProdDiv(/,OpProdDiv(/,LitDouble(-540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "(-540.5 / 75.8) / 764.3");
}

TEST(source_pure_real, op_plus_minus_prod_div_grouping_6) {
    onerut_source_test("OpProdDiv(/,LitDouble(-540.500000),OpProdDiv(/,LitDouble(75.800000),LitDouble(764.300000)))", "-540.5 / (75.8 / 764.3)");
}


