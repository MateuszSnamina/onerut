#include<gtest/gtest.h>
#include<onerut_parser_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(source_pure_integer, literal_1) {
    onerut_source_test("LitLong(6445)", "6445");
}

TEST(source_pure_integereger, literal_2) {
    onerut_source_test("LitLong(-6445)", "-6445");
}

TEST(source_pure_integer, literal_3) {
    onerut_source_test("LitLong(6445)", "+6445");
}

TEST(source_pure_integer, op_plus_munis_1) {
    onerut_source_test("OpPlusMinus(+,LitLong(540),LitLong(75))", "540 + 75");
}

TEST(source_pure_integer, op_plus_munis_2) {
    onerut_source_test("OpPlusMinus(-,LitLong(540),LitLong(75))", "540 - 75");
}

TEST(source_pure_integer, op_plus_munis_3) {
    onerut_source_test("OpPlusMinus(-,LitLong(540),LitLong(75))", "+540 - 75");
}

TEST(source_pure_integer, op_plus_munis_4) {
    onerut_source_test("OpPlusMinus(+,LitLong(-540),LitLong(75))", "-540 + 75");
}

TEST(source_pure_integer, op_plus_munis_5) {
    onerut_source_test("OpPlusMinus(++,LitLong(540),LitLong(75),LitLong(764))", "540 + 75 + 764");
}

//TEST(source_pure_integer, op_plus_munis_6) {
//    ONERUT_TEST(540 + 75 + 764);
//}

TEST(source_pure_integer, op_plus_munis_7) {
    onerut_source_test("OpPlusMinus(-+,LitLong(540),LitLong(75),LitLong(764))", "540 - 75 + 764");
}

TEST(source_pure_integer, op_plus_munis_8) {
    onerut_source_test("OpPlusMinus(-+,LitLong(-540),LitLong(75),LitLong(764))", "-540 - 75 + 764");
}

TEST(source_pure_integer, op_plus_munis_9) {
    onerut_source_test("OpPlusMinus(--,LitLong(-540),LitLong(75),LitLong(764))", "-540 - 75 - 764");
}

TEST(source_pure_integer, op_plus_munis_10) {
    onerut_source_test("OpPlusMinus(+,LitLong(10000000000000000),LitLong(1))", "10000000000000000 + 1");
}

TEST(source_pure_integer, op_prod_div_1) {
    onerut_source_test("OpProdDiv(*,LitLong(540),LitLong(75))", "540 * 75");
}

TEST(source_pure_integer, op_prod_div_2) {
    onerut_source_test("OpProdDiv(/,LitLong(540),LitLong(75))", "540 / 75");
}

TEST(source_pure_integer, op_prod_div_3) {
    onerut_source_test("OpProdDiv(/,LitLong(540),LitLong(75))", "+540 / 75");
}

TEST(source_pure_integer, op_prod_div_4) {
    onerut_source_test("OpProdDiv(*,LitLong(-540),LitLong(75))", "-540 * 75");
}

TEST(source_pure_integer, op_prod_div_5) {
    onerut_source_test("OpProdDiv(**,LitLong(540),LitLong(75),LitLong(764))", "540 * 75 * 764");
}

//TEST(source_pure_integer, op_prod_div_6) {
//    ONERUT_TEST(540 * 75 * 764);
//}

TEST(source_pure_integer, op_prod_div_7) {
    onerut_source_test("OpProdDiv(/*,LitLong(540),LitLong(75),LitLong(764))", "540 / 75 * 764");
}

TEST(source_pure_integer, op_prod_div_8) {
    onerut_source_test("OpProdDiv(//,LitLong(-540),LitLong(75),LitLong(764))", "-540 / 75 / 764");
}

TEST(source_pure_integer, op_plus_minus_prod_div_1) {
    onerut_source_test("OpPlusMinus(-,LitLong(-54),OpProdDiv(*,LitLong(75),LitLong(764)))", "-54 - 75 * 764");
}

TEST(source_pure_integer, op_plus_minus_prod_div_2) {
    onerut_source_test("OpPlusMinus(+,OpProdDiv(*,LitLong(-54),LitLong(75)),LitLong(764))", "-54 * 75 + 764");
}

TEST(source_pure_integer, op_plus_minus_prod_div_3) {
    onerut_source_test("OpPlusMinus(-,LitLong(-54),OpProdDiv(/,LitLong(75),LitLong(764)))", "-54 - 75 / 764");
}

TEST(source_pure_integer, op_plus_minus_prod_div_4) {
    onerut_source_test("OpPlusMinus(+,OpProdDiv(/,LitLong(-54),LitLong(75)),LitLong(764))", "-54 / 75 + 764");
}

TEST(source_pure_integer, simple_grouping_1) {
    onerut_source_test("LitLong(45)", "(45)");
}

TEST(source_pure_integer, simple_grouping_2) {
    onerut_source_test("OpUnaryPlusMinus(+,LitLong(45))", "+(45)");
}

TEST(source_pure_integer, simple_grouping_3) {
    onerut_source_test("OpUnaryPlusMinus(-,LitLong(45))", "-(45)");
}

TEST(source_pure_integer, simple_grouping_4) {
    onerut_source_test("OpUnaryPlusMinus(+,LitLong(-45))", "+(-45)");
}

TEST(source_pure_integer, simple_grouping_5) {
    onerut_source_test("OpUnaryPlusMinus(-,LitLong(-45))", "-(-45)");
}

TEST(source_pure_integer, simple_grouping_6) {
    onerut_source_test("OpUnaryPlusMinus(-,LitLong(-45))", "-((-45))");
}

TEST(source_pure_integer, simple_grouping_7) {
    onerut_source_test("OpUnaryPlusMinus(-,LitLong(-45))", "-([-45])");
}

TEST(source_pure_integer, op_plus_minus_prod_div_grouping_1) {
    onerut_source_test("OpProdDiv(**,LitLong(540),LitLong(75),LitLong(764))", "(540 * 75 * 764)");
}

TEST(source_pure_integer, op_plus_minus_prod_div_grouping_2) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(*,LitLong(540),LitLong(75)),LitLong(764))", "(540 * 75) * 764");
}

TEST(source_pure_integer, op_plus_minus_prod_div_grouping_4) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(/,LitLong(540),LitLong(75)),LitLong(764))", "(540 / 75) * 764");
}

TEST(source_pure_integer, op_plus_minus_prod_div_grouping_5) {
    onerut_source_test("OpProdDiv(/,LitLong(540),OpProdDiv(*,LitLong(75),LitLong(764)))", "540 / (75 * 764)");
}

TEST(source_pure_integer, op_plus_minus_prod_div_grouping_6) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(/,LitLong(-540),LitLong(75)),LitLong(764))", "(-540 / 75) * 764");
}

//TEST(source_pure_integer, op_plus_minus_prod_div_grouping_7) {
//    ONERUT_TEST(-540 / (75 / 764));
//}

TEST(source_pure_integer, op_plus_minus_prod_div_grouping_8) {
    onerut_source_test("OpProdDiv(*,OpPlusMinus(-,LitLong(-54),LitLong(75)),LitLong(764))", "(-54 - 75) * 764");
}

TEST(source_pure_integer, op_plus_minus_prod_div_grouping_9) {
    onerut_source_test("OpPlusMinus(-,LitLong(-54),OpProdDiv(*,LitLong(75),LitLong(764)))", "-54 - (75 * 764)");
}

TEST(source_pure_integer, op_plus_minus_prod_div_grouping_10) {
    onerut_source_test("OpProdDiv(/,LitLong(-54),OpPlusMinus(+,LitLong(75),LitLong(764)))", "-54 / (75 + 764)");
}