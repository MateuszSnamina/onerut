#include<gtest/gtest.h>
#include<onerut_parser_tests/source_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

// [...]

TEST(sourcePureReal, opProdDiv7) {
    onerut_source_test("OpProdDiv(/*,LitDouble(540.500000),LitDouble(75.800000),LitDouble(764.300000))", "540.5 / 75.8 * 764.3");
}

TEST(sourcePureReal, opProdDiv8) {
    onerut_source_test("OpProdDiv(//,LitDouble(-540.500000),LitDouble(75.800000),LitDouble(764.300000))", "-540.5 / 75.8 / 764.3");
}

// [...]

TEST(sourcePureReal, opPlusMinusProdDiv2) {
    onerut_source_test("OpPlusMinus(+,OpProdDiv(*,LitDouble(-540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "-540.5 * 75.8 + 764.3");
}

TEST(sourcePureReal, opPlusMinusProdDiv3) {
    onerut_source_test("OpPlusMinus(-,LitDouble(-540.500000),OpProdDiv(/,LitDouble(75.800000),LitDouble(764.300000)))", "-540.5 - 75.8 / 764.3");
}

TEST(sourcePureReal, opPlusMinusProdDiv4) {
    onerut_source_test("OpPlusMinus(+,OpProdDiv(/,LitDouble(-540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "-540.5 / 75.8 + 764.3");
}

// [...]

TEST(sourcePureReal, opPlusMinusProdDivGrouping1) {
    onerut_source_test("OpProdDiv(**,LitDouble(540.500000),LitDouble(75.800000),LitDouble(764.300000))", "(540.5 * 75.8 * 764.3)");
}

TEST(sourcePureReal, opPlusMinusProdDivGrouping2) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(*,LitDouble(540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "(540.5 * 75.8) * 764.3");
}

TEST(sourcePureReal, opPlusMinusProdDivGrouping3) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(/,LitDouble(540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "(540.5 / 75.8) * 764.3");
}

TEST(sourcePureReal, opPlusMinusProdDivGrouping4) {
    onerut_source_test("OpProdDiv(/,LitDouble(540.500000),OpProdDiv(*,LitDouble(75.800000),LitDouble(764.300000)))", "540.5 / (75.8 * 764.3)");
}

TEST(sourcePureReal, opPlusMinusProdDivGrouping5) {
    onerut_source_test("OpProdDiv(/,OpProdDiv(/,LitDouble(-540.500000),LitDouble(75.800000)),LitDouble(764.300000))", "(-540.5 / 75.8) / 764.3");
}

TEST(sourcePureReal, opPlusMinusProdDivGrouping6) {
    onerut_source_test("OpProdDiv(/,LitDouble(-540.500000),OpProdDiv(/,LitDouble(75.800000),LitDouble(764.300000)))", "-540.5 / (75.8 / 764.3)");
}