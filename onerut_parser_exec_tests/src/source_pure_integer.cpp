#include<gtest/gtest.h>
#include<onerut_parser_tests/source_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(sourcePureInteger, literal1) {
    onerut_source_test("LitLong(6445)", "6445");
}

TEST(sourcePureIntegereger, literal2) {
    onerut_source_test("LitLong(-6445)", "-6445");
}

TEST(sourcePureInteger, literal3) {
    onerut_source_test("LitLong(6445)", "+6445");
}

TEST(sourcePureInteger, opPlusMunis1) {
    onerut_source_test("OpPlusMinus(+,LitLong(540),LitLong(75))", "540 + 75");
}

TEST(sourcePureInteger, opPlusMunis2) {
    onerut_source_test("OpPlusMinus(-,LitLong(540),LitLong(75))", "540 - 75");
}

TEST(sourcePureInteger, opPlusMunis3) {
    onerut_source_test("OpPlusMinus(-,LitLong(540),LitLong(75))", "+540 - 75");
}

TEST(sourcePureInteger, opPlusMunis4) {
    onerut_source_test("OpPlusMinus(+,LitLong(-540),LitLong(75))", "-540 + 75");
}

TEST(sourcePureInteger, opPlusMunis5) {
    onerut_source_test("OpPlusMinus(++,LitLong(540),LitLong(75),LitLong(764))", "540 + 75 + 764");
}

//TEST(sourcePureInteger, opPlusMunis6) {
//    ONERUT_TEST(540 + 75 + 764);
//}

TEST(sourcePureInteger, opPlusMunis7) {
    onerut_source_test("OpPlusMinus(-+,LitLong(540),LitLong(75),LitLong(764))", "540 - 75 + 764");
}

TEST(sourcePureInteger, opPlusMunis8) {
    onerut_source_test("OpPlusMinus(-+,LitLong(-540),LitLong(75),LitLong(764))", "-540 - 75 + 764");
}

TEST(sourcePureInteger, opPlusMunis9) {
    onerut_source_test("OpPlusMinus(--,LitLong(-540),LitLong(75),LitLong(764))", "-540 - 75 - 764");
}

TEST(sourcePureInteger, opPlusMunis10) {
    onerut_source_test("OpPlusMinus(+,LitLong(10000000000000000),LitLong(1))", "10000000000000000 + 1");
}

TEST(sourcePureInteger, opProdDiv1) {
    onerut_source_test("OpProdDiv(*,LitLong(540),LitLong(75))", "540 * 75");
}

TEST(sourcePureInteger, opProdDiv2) {
    onerut_source_test("OpProdDiv(/,LitLong(540),LitLong(75))", "540 / 75");
}

TEST(sourcePureInteger, opProdDiv3) {
    onerut_source_test("OpProdDiv(/,LitLong(540),LitLong(75))", "+540 / 75");
}

TEST(sourcePureInteger, opProdDiv4) {
    onerut_source_test("OpProdDiv(*,LitLong(-540),LitLong(75))", "-540 * 75");
}

TEST(sourcePureInteger, opProdDiv5) {
    onerut_source_test("OpProdDiv(**,LitLong(540),LitLong(75),LitLong(764))", "540 * 75 * 764");
}

//TEST(sourcePureInteger, opProdDiv6) {
//    ONERUT_TEST(540 * 75 * 764);
//}

TEST(sourcePureInteger, opProdDiv7) {
    onerut_source_test("OpProdDiv(/*,LitLong(540),LitLong(75),LitLong(764))", "540 / 75 * 764");
}

TEST(sourcePureInteger, opProdDiv8) {
    onerut_source_test("OpProdDiv(//,LitLong(-540),LitLong(75),LitLong(764))", "-540 / 75 / 764");
}

TEST(sourcePureInteger, opPlusMinusProdDiv1) {
    onerut_source_test("OpPlusMinus(-,LitLong(-54),OpProdDiv(*,LitLong(75),LitLong(764)))", "-54 - 75 * 764");
}

TEST(sourcePureInteger, opPlusMinusProdDiv2) {
    onerut_source_test("OpPlusMinus(+,OpProdDiv(*,LitLong(-54),LitLong(75)),LitLong(764))", "-54 * 75 + 764");
}

TEST(sourcePureInteger, opPlusMinusProdDiv3) {
    onerut_source_test("OpPlusMinus(-,LitLong(-54),OpProdDiv(/,LitLong(75),LitLong(764)))", "-54 - 75 / 764");
}

TEST(sourcePureInteger, opPlusMinusProdDiv4) {
    onerut_source_test("OpPlusMinus(+,OpProdDiv(/,LitLong(-54),LitLong(75)),LitLong(764))", "-54 / 75 + 764");
}

TEST(sourcePureInteger, simpleGrouping1) {
    onerut_source_test("LitLong(45)", "(45)");
}

TEST(sourcePureInteger, simpleGrouping2) {
    onerut_source_test("OpUnaryPlusMinus(+,LitLong(45))", "+(45)");
}

TEST(sourcePureInteger, simpleGrouping3) {
    onerut_source_test("OpUnaryPlusMinus(-,LitLong(45))", "-(45)");
}

TEST(sourcePureInteger, simpleGrouping4) {
    onerut_source_test("OpUnaryPlusMinus(+,LitLong(-45))", "+(-45)");
}

TEST(sourcePureInteger, simpleGrouping5) {
    onerut_source_test("OpUnaryPlusMinus(-,LitLong(-45))", "-(-45)");
}

TEST(sourcePureInteger, simpleGrouping6) {
    onerut_source_test("OpUnaryPlusMinus(-,LitLong(-45))", "-((-45))");
}

TEST(sourcePureInteger, simpleGrouping7) {
    onerut_source_test("OpUnaryPlusMinus(-,LitLong(-45))", "-([-45])");
}

TEST(sourcePureInteger, opPlusMinusProdDivGrouping1) {
    onerut_source_test("OpProdDiv(**,LitLong(540),LitLong(75),LitLong(764))", "(540 * 75 * 764)");
}

TEST(sourcePureInteger, opPlusMinusProdDivGrouping2) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(*,LitLong(540),LitLong(75)),LitLong(764))", "(540 * 75) * 764");
}

TEST(sourcePureInteger, opPlusMinusProdDivGrouping4) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(/,LitLong(540),LitLong(75)),LitLong(764))", "(540 / 75) * 764");
}

TEST(sourcePureInteger, opPlusMinusProdDivGrouping5) {
    onerut_source_test("OpProdDiv(/,LitLong(540),OpProdDiv(*,LitLong(75),LitLong(764)))", "540 / (75 * 764)");
}

TEST(sourcePureInteger, opPlusMinusProdDivGrouping6) {
    onerut_source_test("OpProdDiv(*,OpProdDiv(/,LitLong(-540),LitLong(75)),LitLong(764))", "(-540 / 75) * 764");
}

//TEST(sourcePureInteger, opPlusMinusProdDivGrouping7) {
//    ONERUT_TEST(-540 / (75 / 764));
//}

TEST(sourcePureInteger, opPlusMinusProdDivGrouping8) {
    onerut_source_test("OpProdDiv(*,OpPlusMinus(-,LitLong(-54),LitLong(75)),LitLong(764))", "(-54 - 75) * 764");
}

TEST(sourcePureInteger, opPlusMinusProdDivGrouping9) {
    onerut_source_test("OpPlusMinus(-,LitLong(-54),OpProdDiv(*,LitLong(75),LitLong(764)))", "-54 - (75 * 764)");
}

TEST(sourcePureInteger, opPlusMinusProdDivGrouping10) {
    onerut_source_test("OpProdDiv(/,LitLong(-54),OpPlusMinus(+,LitLong(75),LitLong(764)))", "-54 / (75 + 764)");
}