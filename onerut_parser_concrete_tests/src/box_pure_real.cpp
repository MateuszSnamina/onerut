#include<gtest/gtest.h>
#include<onerut_parser_tests/box_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(boxPureReal, literal1) {
    ONERUT_BOX_VALUE_TEST(6445.);
}

TEST(boxPureReal, literal2) {
    ONERUT_BOX_VALUE_TEST(6445.0);
}

TEST(boxPureReal, literal3) {
    ONERUT_BOX_VALUE_TEST(.6445);
}

TEST(boxPureReal, literal4) {
    ONERUT_BOX_VALUE_TEST(0.6445);
}

TEST(boxPureReal, literal5) {
    ONERUT_BOX_VALUE_TEST(1e5);
}

TEST(boxPureReal, literal6) {
    ONERUT_BOX_VALUE_TEST(1e+5);
}

TEST(boxPureReal, literal7) {
    ONERUT_BOX_VALUE_TEST(+1e-5);
}

TEST(boxPureReal, literal8) {
    ONERUT_BOX_VALUE_TEST(inf);
}

TEST(boxPureReal, literal9) {
    ONERUT_BOX_VALUE_TEST(-6445.);
}

TEST(boxPureReal, literal10) {
    ONERUT_BOX_VALUE_TEST(-.6445);
}

TEST(boxPureReal, literal11) {
    ONERUT_BOX_VALUE_TEST(-inf);
}

TEST(boxPureReal, opPlusMinus1) {
    ONERUT_BOX_VALUE_TEST(540.5 + 7.8);
}

TEST(boxPureReal, opPlusMinus2) {
    ONERUT_BOX_VALUE_TEST(540.5 - 75.8);
}

TEST(boxPureReal, opPlusMinus3) {
    ONERUT_BOX_VALUE_TEST(+540.5 - 75.8);
}

TEST(boxPureReal, opPlusMinus4) {
    ONERUT_BOX_VALUE_TEST(-540.5 + 75.8);
}

TEST(boxPureReal, opPlusMinus5) {
    ONERUT_BOX_VALUE_TEST(540.5 + 75.8 + 764.3);
}

TEST(boxPureReal, opPlusMinus6) {
    ONERUT_BOX_VALUE_TEST(540.5 + 75.8 + 764.3);
}

TEST(boxPureReal, opPlusMinus7) {
    ONERUT_BOX_VALUE_TEST(540.5 - 75.8 + 764.3);
}

TEST(boxPureReal, opPlusMinus8) {
    ONERUT_BOX_VALUE_TEST(-540.5 - 75.8 + 764.3);
}

TEST(boxPureReal, opPlusMinus9) {
    ONERUT_BOX_VALUE_TEST(-540.5 - 75.8 - 764.3);
}

TEST(boxPureReal, opPlusMinus10) {
    ONERUT_BOX_VALUE_TEST(10000000000000000. + 1.);
}

TEST(boxPureReal, boxPureReal1) {
    ONERUT_BOX_VALUE_TEST(540.5 * 75.8);
}

TEST(boxPureReal, boxPureReal2) {
    ONERUT_BOX_VALUE_TEST(540.5 / 75.8);
}

TEST(boxPureReal, boxPureReal3) {
    ONERUT_BOX_VALUE_TEST(+540.5 / 75.8);
}

TEST(boxPureReal, boxPureReal4) {
    ONERUT_BOX_VALUE_TEST(-540.5 * 75.8);
}

TEST(boxPureReal, boxPureReal5) {
    ONERUT_BOX_VALUE_TEST(540.5 * 75.8 * 764.3);
}

TEST(boxPureReal, boxPureReal6) {
    ONERUT_BOX_VALUE_TEST(540.5 * 75.8 * 764.3);
}

TEST(boxPureReal, boxPureReal7) {
    ONERUT_BOX_VALUE_TEST(540.5 / 75.8 * 764.3);
}

TEST(boxPureReal, boxPureReal8) {
    ONERUT_BOX_VALUE_TEST(-540.5 / 75.8 / 764.3);
}

TEST(boxPureReal, opPlusMinusProdDiv1) {
    ONERUT_BOX_VALUE_TEST(-540.5 - 75.8 * 764.3);
}

TEST(boxPureReal, opPlusMinusProdDiv2) {
    ONERUT_BOX_VALUE_TEST(-540.5 * 75.8 + 764.3);
}

TEST(boxPureReal, opPlusMinusProdDiv3) {
    ONERUT_BOX_VALUE_TEST(-540.5 - 75.8 / 764.3);
}

TEST(boxPureReal, opPlusMinusProdDiv4) {
    ONERUT_BOX_VALUE_TEST(-540.5 / 75.8 + 764.3);
}

TEST(boxPureReal, simpleGrouping1) {
    ONERUT_BOX_VALUE_TEST((450.5));
}

TEST(boxPureReal, simpleGrouping2) {
    ONERUT_BOX_VALUE_TEST(+(450.5));
}

TEST(boxPureReal, simpleGrouping3) {
    ONERUT_BOX_VALUE_TEST(-(450.5));
}

TEST(boxPureReal, simpleGrouping4) {
    ONERUT_BOX_VALUE_TEST(+(-45.5));
}

TEST(boxPureReal, simpleGrouping5) {
    ONERUT_BOX_VALUE_TEST(-(-45.5));
}

TEST(boxPureReal, simpleGrouping6) {
    ONERUT_BOX_VALUE_TEST(-((-45.5)));
}

TEST(boxPureReal, simpleGrouping7) {
    BASIC_ONERUT_BOX_VALUE_TEST(-((-45.5)), -([-45.5]));
}

TEST(boxPureReal, opPlusMinusProdDivGrouping1) {
    ONERUT_BOX_VALUE_TEST((540.5 * 75.8 * 764.3));
}

TEST(boxPureReal, opPlusMinusProdDivGrouping2) {
    ONERUT_BOX_VALUE_TEST((540.5 * 75.8) * 764.3);
}

TEST(boxPureReal, opPlusMinusProdDivGrouping3) {
    ONERUT_BOX_VALUE_TEST((540.5 / 75.8) * 764.3);
}

TEST(boxPureReal, opPlusMinusProdDivGrouping4) {
    ONERUT_BOX_VALUE_TEST(540.5 / (75.8 * 764.3));
}

TEST(boxPureReal, opPlusMinusProdDivGrouping5) {
    ONERUT_BOX_VALUE_TEST((-540.5 / 75.8) / 764.3);
}

TEST(boxPureReal, opPlusMinusProdDivGrouping6) {
    ONERUT_BOX_VALUE_TEST(-540.5 / (75.8 / 764.3));
}

TEST(boxPureReal, opPlusMinusProdDivGrouping7) {
    ONERUT_BOX_VALUE_TEST((-54 - 75.8) * 764.3);
}

TEST(boxPureReal, opPlusMinusProdDivGrouping8) {
    ONERUT_BOX_VALUE_TEST(-54 - (75.8 * 764.3));
}

TEST(boxPureReal, opPlusMinusProdDivGrouping9) {
    ONERUT_BOX_VALUE_TEST(-54 / (75.8 + 764.3));
}
