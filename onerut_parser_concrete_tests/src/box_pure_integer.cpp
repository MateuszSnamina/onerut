#include<gtest/gtest.h>
#include<onerut_parser_tests/box_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(boxPureInteger, literal1) {
    ONERUT_BOX_VALUE_TEST(6445);
}

TEST(boxPureInteger, literal2) {
    ONERUT_BOX_VALUE_TEST(-6445);
}

TEST(boxPureInteger, literal3) {
    ONERUT_BOX_VALUE_TEST(+6445);
}

TEST(boxPureInteger, opPlusMinus1) {
    ONERUT_BOX_VALUE_TEST(540 + 75);
}

TEST(boxPureInteger, opPlusMinus2) {
    ONERUT_BOX_VALUE_TEST(540 - 75);
}

TEST(boxPureInteger, opPlusMinus3) {
    ONERUT_BOX_VALUE_TEST(+540 - 75);
}

TEST(boxPureInteger, opPlusMinus4) {
    ONERUT_BOX_VALUE_TEST(-540 + 75);
}

TEST(boxPureInteger, opPlusMinus5) {
    ONERUT_BOX_VALUE_TEST(540 + 75 + 764);
}

TEST(boxPureInteger, opPlusMinus6) {
    ONERUT_BOX_VALUE_TEST(540 + 75 + 764);
}

TEST(boxPureInteger, opPlusMinus7) {
    ONERUT_BOX_VALUE_TEST(540 - 75 + 764);
}

TEST(boxPureInteger, opPlusMinus8) {
    ONERUT_BOX_VALUE_TEST(-540 - 75 + 764);
}

TEST(boxPureInteger, opPlusMinus9) {
    ONERUT_BOX_VALUE_TEST(-540 - 75 - 764);
}

TEST(boxPureInteger, opPlusMinus10) {
    BASIC_ONERUT_BOX_VALUE_TEST(10000000000000000l + 1, 10000000000000000 + 1);
}

TEST(boxPureInteger, opProdDiv1) {
    ONERUT_BOX_VALUE_TEST(540 * 75);
}

TEST(boxPureInteger, opProdDiv2) {
    ONERUT_BOX_VALUE_TEST(540 / 75);
}

TEST(boxPureInteger, opProdDiv3) {
    ONERUT_BOX_VALUE_TEST(+540 / 75);
}

TEST(boxPureInteger, opProdDiv4) {
    ONERUT_BOX_VALUE_TEST(-540 * 75);
}

TEST(boxPureInteger, opProdDiv5) {
    ONERUT_BOX_VALUE_TEST(540 * 75 * 764);
}

TEST(boxPureInteger, opProdDiv6) {
    ONERUT_BOX_VALUE_TEST(540 * 75 * 764);
}

TEST(boxPureInteger, opProdDiv7) {
    ONERUT_BOX_VALUE_TEST(540 / 75 * 764);
}

TEST(boxPureInteger, opProdDiv8) {
    ONERUT_BOX_VALUE_TEST(-540 / 75 / 764);
}

TEST(boxPureInteger, opPlusMinusProdDiv1) {
    ONERUT_BOX_VALUE_TEST(-54 - 75 * 764);
}

TEST(boxPureInteger, opPlusMinusProdDiv2) {
    ONERUT_BOX_VALUE_TEST(-54 * 75 + 764);
}

TEST(boxPureInteger, opPlusMinusProdDiv3) {
    ONERUT_BOX_VALUE_TEST(-54 - 75 / 764);
}

TEST(boxPureInteger, opPlusMinusProdDiv4) {
    ONERUT_BOX_VALUE_TEST(-54 / 75 + 764);
}

TEST(boxPureInteger, simpleGrouping1) {
    ONERUT_BOX_VALUE_TEST((45));
}

TEST(boxPureInteger, simpleGrouping2) {
    ONERUT_BOX_VALUE_TEST(+(45));
}

TEST(boxPureInteger, simpleGrouping3) {
    ONERUT_BOX_VALUE_TEST(-(45));
}

TEST(boxPureInteger, simpleGrouping4) {
    ONERUT_BOX_VALUE_TEST(+(-45));
}

TEST(boxPureInteger, simpleGrouping5) {
    ONERUT_BOX_VALUE_TEST(-(-45));
}

TEST(boxPureInteger, simpleGrouping6) {
    ONERUT_BOX_VALUE_TEST(-((-45)));
}

TEST(boxPureInteger, simpleGrouping7) {
    BASIC_ONERUT_BOX_VALUE_TEST(-((-45)), -([-45]));
}

TEST(boxPureInteger, opPlusMinusProdDivgrouping1) {
    ONERUT_BOX_VALUE_TEST((540 * 75 * 764));
}

TEST(boxPureInteger, opPlusMinusProdDivgrouping2) {
    ONERUT_BOX_VALUE_TEST((540 * 75) * 764);
}

TEST(boxPureInteger, opPlusMinusProdDivgrouping4) {
    ONERUT_BOX_VALUE_TEST((540 / 75) * 764);
}

TEST(boxPureInteger, opPlusMinusProdDivgrouping5) {
    ONERUT_BOX_VALUE_TEST(540 / (75 * 764));
}

TEST(boxPureInteger, opPlusMinusProdDivgrouping6) {
    ONERUT_BOX_VALUE_TEST((-540 / 75) / 764);
}

//TEST(boxPureInteger, opPlusMinusProdDivgrouping7) {
//    ONERUT_BOX_VALUE_TEST(-540 / (75 / 764));
//}

TEST(boxPureInteger, opPlusMinusProdDivgrouping8) {
    ONERUT_BOX_VALUE_TEST((-54 - 75) * 764);
}

TEST(boxPureInteger, opPlusMinusProdDivgrouping9) {
    ONERUT_BOX_VALUE_TEST(-54 - (75 * 764));
}

TEST(boxPureInteger, opPlusMinusProdDivgrouping10) {
    ONERUT_BOX_VALUE_TEST(-54 / (75 + 764));
}