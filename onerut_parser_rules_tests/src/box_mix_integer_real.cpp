#include<gtest/gtest.h>
#include<onerut_parser_tests/box_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(boxMixIntegerReal, opPlusMunis1) {
    ONERUT_BOX_VALUE_TEST(540 + 7.8);
}

TEST(boxMixIntegerReal, opPlusMunis2) {
    ONERUT_BOX_VALUE_TEST(540.5 + 7);
}

TEST(boxMixIntegerReal, opPlusMunis3) {
    ONERUT_BOX_VALUE_TEST(540 - 75.8);
}

TEST(boxMixIntegerReal, opPlusMunis4) {
    ONERUT_BOX_VALUE_TEST(540.5 - 75);
}

TEST(boxMixIntegerReal, opPlusMunis5) {
    ONERUT_BOX_VALUE_TEST(540 + 75 + 764.3);
}

TEST(boxMixIntegerReal, opPlusMunis6) {
    ONERUT_BOX_VALUE_TEST(540.5 + 75 + 764.3);
}

TEST(boxMixIntegerReal, opPlusMunis7) {
    ONERUT_BOX_VALUE_TEST(540.5 - 75 + 764);
}

TEST(boxMixIntegerReal, opPlusMunis8) {
    ONERUT_BOX_VALUE_TEST(-540 - 75.8 + 764);
}

TEST(boxMixIntegerReal, opPlusMunis10) {
    BASIC_ONERUT_BOX_VALUE_TEST(10000000000000000l + 1., 10000000000000000 + 1.);
}

TEST(boxMixIntegerReal, opProdDiv1) {
    ONERUT_BOX_VALUE_TEST(540 * 75.8);
}

TEST(boxMixIntegerReal, opProdDiv2) {
    ONERUT_BOX_VALUE_TEST(540.5 * 75);
}

TEST(boxMixIntegerReal, opProdDiv3) {
    ONERUT_BOX_VALUE_TEST(540 / 75.8);
}

TEST(boxMixIntegerReal, opProdDiv4) {
    ONERUT_BOX_VALUE_TEST(+540.5 / 75);
}

TEST(boxMixIntegerReal, opProdDiv5) {
    ONERUT_BOX_VALUE_TEST(540 * 75 * 764.3);
}

TEST(boxMixIntegerReal, opProdDiv6) {
    ONERUT_BOX_VALUE_TEST(540 * 75.8 * 764.3);
}

TEST(boxMixIntegerReal, opPlusMinusProdDiv1) {
    ONERUT_BOX_VALUE_TEST(-540.5 - 75 / 764);
}

TEST(boxMixIntegerReal, opPlusMinusProdDivGrouping8) {
    ONERUT_BOX_VALUE_TEST((-54 - 75.8) * 764.3);
}

TEST(boxMixIntegerReal, opPlusMinusProdDivGrouping9) {
    ONERUT_BOX_VALUE_TEST(-54 - (75.8 * 764.3));
}

TEST(boxMixIntegerReal, opPlusMinusProdDivGrouping10) {
    ONERUT_BOX_VALUE_TEST(-54 / (75.8 + 764.3));
}