#include<gtest/gtest.h>
#include<onerut_parser_tests/source_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(sourceMixIntegerReal, opPlusMunis1) {
    onerut_source_test("OpPlusMinus(+,LitLong(540),LitDouble(7.800000))", "540 + 7.8");
}

TEST(sourceMixIntegerReal, opPlusMunis2) {
    onerut_source_test("OpPlusMinus(+,LitDouble(540.500000),LitLong(7))", "540.5 + 7");
}

TEST(sourceMixIntegerReal, opPlusMunis3) {
    onerut_source_test("OpPlusMinus(-,LitLong(540),LitDouble(75.800000))", "540 - 75.8");
}

TEST(sourceMixIntegerReal, opPlusMunis4) {
    onerut_source_test("OpPlusMinus(-,LitDouble(540.500000),LitLong(75))", "540.5 - 75");
}

TEST(sourceMixIntegerReal, opPlusMunis5) {
    onerut_source_test("OpPlusMinus(++,LitLong(540),LitLong(75),LitDouble(764.300000))", "540 + 75 + 764.3");
}

TEST(sourceMixIntegerReal, opPlusMunis6) {
    onerut_source_test("OpPlusMinus(++,LitDouble(540.500000),LitLong(75),LitDouble(764.300000))", "540.5 + 75 + 764.3");
}

TEST(sourceMixIntegerReal, opPlusMunis7) {
    onerut_source_test("OpPlusMinus(-+,LitDouble(540.500000),LitLong(75),LitLong(764))", "540.5 - 75 + 764");
}

TEST(sourceMixIntegerReal, opPlusMunis8) {
    onerut_source_test("OpPlusMinus(-+,LitLong(-540),LitDouble(75.800000),LitLong(764))", "-540 - 75.8 + 764");
}

TEST(sourceMixIntegerReal, opProdDiv1) {
    onerut_source_test("OpProdDiv(*,LitLong(540),LitDouble(75.800000))", "540 * 75.8");
}

TEST(sourceMixIntegerReal, opProdDiv2) {
    onerut_source_test("OpProdDiv(*,LitDouble(540.500000),LitLong(75))", "540.5 * 75");
}

TEST(sourceMixIntegerReal, opProdDiv3) {
    onerut_source_test("OpProdDiv(/,LitLong(540),LitDouble(75.800000))", "540 / 75.8");
}

TEST(sourceMixIntegerReal, opProdDiv4) {
    onerut_source_test("OpProdDiv(/,LitDouble(540.500000),LitLong(75))", "+540.5 / 75");
}

TEST(sourceMixIntegerReal, opProdDiv5) {
    onerut_source_test("OpProdDiv(**,LitLong(540),LitLong(75),LitDouble(764.300000))", "540 * 75 * 764.3");
}

TEST(sourceMixIntegerReal, opProdDiv6) {
    onerut_source_test("OpProdDiv(**,LitLong(540),LitDouble(75.800000),LitDouble(764.300000))", "540 * 75.8 * 764.3");
}

TEST(sourceMixIntegerReal, opPlusMinusProdDiv1) {
    onerut_source_test("OpPlusMinus(-,LitDouble(-540.500000),OpProdDiv(/,LitLong(75),LitLong(764)))", "-540.5 - 75 / 764");
}

TEST(sourceMixIntegerReal, opPlusMinus10) {
    onerut_source_test("OpPlusMinus(+,LitLong(10000000000000000),LitDouble(1.000000))", "10000000000000000 + 1.");
}

TEST(sourceMixIntegerReal, opPlusMinusProdDivGrouping8) {
    onerut_source_test("OpProdDiv(*,OpPlusMinus(-,LitLong(-54),LitDouble(75.800000)),LitDouble(764.300000))", "(-54 - 75.8) * 764.3");
}

TEST(sourceMixIntegerReal, opPlusMinusProdDivgrouping9) {
    onerut_source_test("OpPlusMinus(-,LitLong(-54),OpProdDiv(*,LitDouble(75.800000),LitDouble(764.300000)))", "-54 - (75.8 * 764.3)");
}

TEST(sourceMixIntegerReal, opPlusMinusProdDivgrouping10) {
    onerut_source_test("OpProdDiv(/,LitLong(-54),OpPlusMinus(+,LitDouble(75.800000),LitDouble(764.300000)))", "-54 / (75.8 + 764.3)");
}