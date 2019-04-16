#include<gtest/gtest.h>
#include<onerut_parser_tests/box_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(boxPureComplex, literal1) {
    ONERUT_BOX_VALUE_TEST(6445.i);
}

TEST(boxPureComplex, literal2) {
    ONERUT_BOX_VALUE_TEST(6445i);
}

TEST(boxPureComplex, literal3) {
    ONERUT_BOX_VALUE_TEST(.6445i);
}

TEST(boxPureComplex, literal4) {
    ONERUT_BOX_VALUE_TEST(0.6445i);
}

TEST(boxPureComplex, literal5) {
    ONERUT_BOX_VALUE_TEST(1e5i);
}

TEST(boxPureComplex, literal6) {
    ONERUT_BOX_VALUE_TEST(1e+5i);
}

TEST(boxPureComplex, literal7) {
    ONERUT_BOX_VALUE_TEST(+1e-5i);
}

TEST(boxPureComplex, literal8) {
    BASIC_ONERUT_BOX_VALUE_TEST(std::complex<double>(0, inf), infi);
}

TEST(boxPureComplex, literal9) {
    ONERUT_BOX_VALUE_TEST(-6445.i);
}

TEST(boxPureComplex, literal10) {
    ONERUT_BOX_VALUE_TEST(-.6445i);
}

TEST(boxPureComplex, literal11) {
    BASIC_ONERUT_BOX_VALUE_TEST(std::complex<double>(0, -inf), -infi);
}

TEST(boxPureComplex, opPlusMinus1) {
    ONERUT_BOX_VALUE_TEST(540.5i + 7.8i);
}

TEST(boxPureComplex, opPlusMinus2) {
    ONERUT_BOX_VALUE_TEST(540.5i - 75.8i);
}

TEST(boxPureComplex, opPlusMinus3) {
    ONERUT_BOX_VALUE_TEST(+540.5i - 75.8i);
}

TEST(boxPureComplex, opPlusMinus4) {
    ONERUT_BOX_VALUE_TEST(-540.5i + 75.8i);
}

TEST(boxPureComplex, opPlusMinus5) {
    ONERUT_BOX_VALUE_TEST(540.5i + 75.8i + 764.3i);
}

TEST(boxPureComplex, opPlusMinus6) {
    ONERUT_BOX_VALUE_TEST(540.5i + 75.8i + 764.3i);
}

TEST(boxPureComplex, opPlusMinus7) {
    ONERUT_BOX_VALUE_TEST(540.5i - 75.8i + 764.3i);
}

TEST(boxPureComplex, opPlusMinus8) {
    ONERUT_BOX_VALUE_TEST(-540.5i - 75.8i + 764.3i);
}

TEST(boxPureComplex, opPlusMinus9) {
    ONERUT_BOX_VALUE_TEST(-540.5i - 75.8i - 764.3i);
}

TEST(boxPureComplex, opPlusMinus10) {
    ONERUT_BOX_VALUE_TEST(10000000000000000.i + 1.i);
}

TEST(boxPureComplex, opProdDiv1) {
    ONERUT_BOX_VALUE_TEST(540.5i * 75.8i);
}

TEST(boxPureComplex, opProdDiv2) {
    ONERUT_BOX_VALUE_TEST(540.5i / 75.8i);
}

TEST(boxPureComplex, opProdDiv3) {
    ONERUT_BOX_VALUE_TEST(+540.5i / 75.8i);
}

TEST(boxPureComplex, opProdDiv4) {
    ONERUT_BOX_VALUE_TEST(-540.5i * 75.8i);
}

TEST(boxPureComplex, opProdDiv5) {
    ONERUT_BOX_VALUE_TEST(540.5i * 75.8i * 764.3i);
}

TEST(boxPureComplex, opProdDiv6) {
    ONERUT_BOX_VALUE_TEST(540.5i * 75.8i * 764.3i);
}

TEST(boxPureComplex, opProdDiv7) {
    ONERUT_BOX_VALUE_TEST(540.5i / 75.8i * 764.3i);
}

TEST(boxPureComplex, opProdDiv8) {
    ONERUT_BOX_VALUE_TEST(-540.5i / 75.8i / 764.3i);
}

TEST(boxPureComplex, opPlusMinusProdDiv1) {
    ONERUT_BOX_VALUE_TEST(-540.5i - 75.8i * 764.3i);
}

TEST(boxPureComplex, opPlusMinusProdDiv2) {
    ONERUT_BOX_VALUE_TEST(-540.5i * 75.8i + 764.3i);
}

TEST(boxPureComplex, opPlusMinusProdDiv3) {
    ONERUT_BOX_VALUE_TEST(-540.5i - 75.8i / 764.3i);
}

TEST(boxPureComplex, opPlusMinusProdDiv4) {
    ONERUT_BOX_VALUE_TEST(-540.5i / 75.8i + 764.3i);
}

TEST(boxPureComplex, simpleGrouping1) {
    ONERUT_BOX_VALUE_TEST((450.5i));
}

TEST(boxPureComplex, simpleGrouping2) {
    ONERUT_BOX_VALUE_TEST(+(450.5i));
}

TEST(boxPureComplex, simpleGrouping3) {
    ONERUT_BOX_VALUE_TEST(-(450.5i));
}

TEST(boxPureComplex, simpleGrouping4) {
    ONERUT_BOX_VALUE_TEST(+(-45.5i));
}

TEST(boxPureComplex, simpleGrouping5) {
    ONERUT_BOX_VALUE_TEST(-(-45.5i));
}

TEST(boxPureComplex, simpleGrouping6) {
    ONERUT_BOX_VALUE_TEST(-((-45.5i)));
}

TEST(boxPureComplex, simpleGrouping7) {
    BASIC_ONERUT_BOX_VALUE_TEST(-((-45.5i)), -([-45.5i]));
}

TEST(boxPureComplex, opPlusMinusProdDivGrouping1) {
    ONERUT_BOX_VALUE_TEST((540.5i * 75.8i * 764.3i));
}

TEST(boxPureComplex, opPlusMinusProdDivGrouping2) {
    ONERUT_BOX_VALUE_TEST((540.5i * 75.8i) * 764.3i);
}

TEST(boxPureComplex, opPlusMinusProdDivGrouping3) {
    ONERUT_BOX_VALUE_TEST((540.5i / 75.8i) * 764.3i);
}

TEST(boxPureComplex, opPlusMinusProdDivGrouping4) {
    ONERUT_BOX_VALUE_TEST(540.5i / (75.8i * 764.3i));
}

TEST(boxPureComplex, opPlusMinusProdDivGrouping5) {
    ONERUT_BOX_VALUE_TEST((-540.5i / 75.8i) / 764.3i);
}

TEST(boxPureComplex, opPlusMinusProdDivGrouping6) {
    ONERUT_BOX_VALUE_TEST(-540.5i / (75.8i / 764.3i));
}

TEST(boxPureComplex, opPlusMinusProdDivGrouping7) {
    ONERUT_BOX_VALUE_TEST((-54i - 75.8i) * 764.3i);
}

TEST(boxPureComplex, opPlusMinusProdDivGrouping8) {
    ONERUT_BOX_VALUE_TEST(-54i - (75.8i * 764.3i));
}

TEST(boxPureComplex, opPlusMinusProdDivGrouping9) {
    ONERUT_BOX_VALUE_TEST(-54i / (75.8i + 764.3i));
}