#include<gtest/gtest.h>
#include<onerut_parser_tests/box_common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(box_pure_complex, literal_1) {
    ONERUT_BOX_VALUE_TEST(6445.i);
}

TEST(box_pure_complex, literal_2) {
    ONERUT_BOX_VALUE_TEST(6445i);
}

TEST(box_pure_complex, literal_3) {
    ONERUT_BOX_VALUE_TEST(.6445i);
}

TEST(box_pure_complex, literal_4) {
    ONERUT_BOX_VALUE_TEST(0.6445i);
}

TEST(box_pure_complex, literal_5) {
    ONERUT_BOX_VALUE_TEST(1e5i);
}

TEST(box_pure_complex, literal_6) {
    ONERUT_BOX_VALUE_TEST(1e+5i);
}

TEST(box_pure_complex, literal_7) {
    ONERUT_BOX_VALUE_TEST(+1e-5i);
}

TEST(box_pure_complex, literal_8) {
    BASIC_ONERUT_BOX_VALUE_TEST(inf * 1i, infi);
}

TEST(box_pure_complex, literal_9) {
    ONERUT_BOX_VALUE_TEST(-6445.i);
}

TEST(box_pure_complex, literal_10) {
    ONERUT_BOX_VALUE_TEST(-.6445i);
}

TEST(box_pure_complex, literal_11) {
    BASIC_ONERUT_BOX_VALUE_TEST(-inf * 1i, -infi);
}

TEST(box_pure_complex, op_plus_munis_1) {
    ONERUT_BOX_VALUE_TEST(540.5i + 7.8i);
}

TEST(box_pure_complex, op_plus_munis_2) {
    ONERUT_BOX_VALUE_TEST(540.5i - 75.8i);
}

TEST(box_pure_complex, op_plus_munis_3) {
    ONERUT_BOX_VALUE_TEST(+540.5i - 75.8i);
}

TEST(box_pure_complex, op_plus_munis_4) {
    ONERUT_BOX_VALUE_TEST(-540.5i + 75.8i);
}

TEST(box_pure_complex, op_plus_munis_5) {
    ONERUT_BOX_VALUE_TEST(540.5i + 75.8i + 764.3i);
}

TEST(box_pure_complex, op_plus_munis_6) {
    ONERUT_BOX_VALUE_TEST(540.5i + 75.8i + 764.3i);
}

TEST(box_pure_complex, op_plus_munis_7) {
    ONERUT_BOX_VALUE_TEST(540.5i - 75.8i + 764.3i);
}

TEST(box_pure_complex, op_plus_munis_8) {
    ONERUT_BOX_VALUE_TEST(-540.5i - 75.8i + 764.3i);
}

TEST(box_pure_complex, op_plus_munis_9) {
    ONERUT_BOX_VALUE_TEST(-540.5i - 75.8i - 764.3i);
}

TEST(box_pure_complex, op_plus_minus_10) {
    ONERUT_BOX_VALUE_TEST(10000000000000000.i + 1.i);
}

TEST(box_pure_complex, op_prod_div_1) {
    ONERUT_BOX_VALUE_TEST(540.5i * 75.8i);
}

TEST(box_pure_complex, op_prod_div_2) {
    ONERUT_BOX_VALUE_TEST(540.5i / 75.8i);
}

TEST(box_pure_complex, op_prod_div_3) {
    ONERUT_BOX_VALUE_TEST(+540.5i / 75.8i);
}

TEST(box_pure_complex, op_prod_div_4) {
    ONERUT_BOX_VALUE_TEST(-540.5i * 75.8i);
}

TEST(box_pure_complex, op_prod_div_5) {
    ONERUT_BOX_VALUE_TEST(540.5i * 75.8i * 764.3i);
}

TEST(box_pure_complex, op_prod_div_6) {
    ONERUT_BOX_VALUE_TEST(540.5i * 75.8i * 764.3i);
}

TEST(box_pure_complex, op_prod_div_7) {
    ONERUT_BOX_VALUE_TEST(540.5i / 75.8i * 764.3i);
}

TEST(box_pure_complex, op_prod_div_8) {
    ONERUT_BOX_VALUE_TEST(-540.5i / 75.8i / 764.3i);
}

TEST(box_pure_complex, op_plus_minus_prod_div_1) {
    ONERUT_BOX_VALUE_TEST(-540.5i - 75.8i * 764.3i);
}

TEST(box_pure_complex, op_plus_minus_prod_div_2) {
    ONERUT_BOX_VALUE_TEST(-540.5i * 75.8i + 764.3i);
}

TEST(box_pure_complex, op_plus_minus_prod_div_3) {
    ONERUT_BOX_VALUE_TEST(-540.5i - 75.8i / 764.3i);
}

TEST(box_pure_complex, op_plus_minus_prod_div_4) {
    ONERUT_BOX_VALUE_TEST(-540.5i / 75.8i + 764.3i);
}

TEST(box_pure_complex, simple_grouping_1) {
    ONERUT_BOX_VALUE_TEST((450.5i));
}

TEST(box_pure_complex, simple_grouping_2) {
    ONERUT_BOX_VALUE_TEST(+(450.5i));
}

TEST(box_pure_complex, simple_grouping_3) {
    ONERUT_BOX_VALUE_TEST(-(450.5i));
}

TEST(box_pure_complex, simple_grouping_4) {
    ONERUT_BOX_VALUE_TEST(+(-45.5i));
}

TEST(box_pure_complex, simple_grouping_5) {
    ONERUT_BOX_VALUE_TEST(-(-45.5i));
}

TEST(box_pure_complex, simple_grouping_6) {
    ONERUT_BOX_VALUE_TEST(-((-45.5i)));
}

TEST(box_pure_complex, simple_grouping_7) {
    BASIC_ONERUT_BOX_VALUE_TEST(-((-45.5i)), -([-45.5i]));
}

TEST(box_pure_complex, op_plus_minus_prod_div_grouping_1) {
    ONERUT_BOX_VALUE_TEST((540.5i * 75.8i * 764.3i));
}

TEST(box_pure_complex, op_plus_minus_prod_div_grouping_2) {
    ONERUT_BOX_VALUE_TEST((540.5i * 75.8i) * 764.3i);
}

TEST(box_pure_complex, op_plus_minus_prod_div_grouping_3) {
    ONERUT_BOX_VALUE_TEST((540.5i / 75.8i) * 764.3i);    
}

TEST(box_pure_complex, op_plus_minus_prod_div_grouping_4) {
    ONERUT_BOX_VALUE_TEST(540.5i / (75.8i * 764.3i));
}

TEST(box_pure_complex, op_plus_minus_prod_div_grouping_5) {
    ONERUT_BOX_VALUE_TEST((-540.5i / 75.8i) / 764.3i);
}

TEST(box_pure_complex, op_plus_minus_prod_div_grouping_6) {
    ONERUT_BOX_VALUE_TEST(-540.5i / (75.8i / 764.3i));
}

TEST(box_pure_complex, op_plus_minus_prod_div_grouping_7) {
    ONERUT_BOX_VALUE_TEST((-54i - 75.8i) * 764.3i);
}

TEST(box_pure_complex, op_plus_minus_prod_div_grouping_8) {
    ONERUT_BOX_VALUE_TEST(-54i - (75.8i * 764.3i));
}

TEST(box_pure_complex, op_plus_minus_prod_div_grouping_9) {
    ONERUT_BOX_VALUE_TEST(-54i / (75.8i + 764.3i));    
}