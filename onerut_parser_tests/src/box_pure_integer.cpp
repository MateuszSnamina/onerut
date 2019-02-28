#include<gtest/gtest.h>
#include<onerut_parser_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(box_pure_integer, literal_1) {
    ONERUT_TEST(6445);
}

TEST(box_pure_integer, literal_2) {
    ONERUT_TEST(-6445);
}

TEST(box_pure_integer, literal_3) {
    ONERUT_TEST(+6445);
}

TEST(box_pure_integer, op_plus_munis_1) {
    ONERUT_TEST(540 + 75);
}

TEST(box_pure_integer, op_plus_munis_2) {
    ONERUT_TEST(540 - 75);
}

TEST(box_pure_integer, op_plus_munis_3) {
    ONERUT_TEST(+540 - 75);
}

TEST(box_pure_integer, op_plus_munis_4) {
    ONERUT_TEST(-540 + 75);
}

TEST(box_pure_integer, op_plus_munis_5) {
    ONERUT_TEST(540 + 75 + 764);
}

TEST(box_pure_integer, op_plus_munis_6) {
    ONERUT_TEST(540 + 75 + 764);
}

TEST(box_pure_integer, op_plus_munis_7) {
    ONERUT_TEST(540 - 75 + 764);
}

TEST(box_pure_integer, op_plus_munis_8) {
    ONERUT_TEST(-540 - 75 + 764);
}

TEST(box_pure_integer, op_plus_munis_9) {
    ONERUT_TEST(-540 - 75 - 764);
}

TEST(box_pure_integer, op_plus_munis_10) {
    BASIC_ONERUT_TEST(10000000000000000l + 1, 10000000000000000 + 1);
}

TEST(box_pure_integer, op_prod_div_1) {
    ONERUT_TEST(540 * 75);
}

TEST(box_pure_integer, op_prod_div_2) {
    ONERUT_TEST(540 / 75);
}

TEST(box_pure_integer, op_prod_div_3) {
    ONERUT_TEST(+540 / 75);
}

TEST(box_pure_integer, op_prod_div_4) {
    ONERUT_TEST(-540 * 75);
}

TEST(box_pure_integer, op_prod_div_5) {
    ONERUT_TEST(540 * 75 * 764);
}

TEST(box_pure_integer, op_prod_div_6) {
    ONERUT_TEST(540 * 75 * 764);
}

TEST(box_pure_integer, op_prod_div_7) {
    ONERUT_TEST(540 / 75 * 764);
}

TEST(box_pure_integer, op_prod_div_8) {
    ONERUT_TEST(-540 / 75 / 764);
}

TEST(box_pure_integer, op_plus_minus_prod_div_1) {
    ONERUT_TEST(-54 - 75 * 764);
}

TEST(box_pure_integer, op_plus_minus_prod_div_2) {
    ONERUT_TEST(-54 * 75 + 764);
}

TEST(box_pure_integer, op_plus_minus_prod_div_3) {
    ONERUT_TEST(-54 - 75 / 764);
}

TEST(box_pure_integer, op_plus_minus_prod_div_4) {
    ONERUT_TEST(-54 / 75 + 764);
}

TEST(box_pure_integer, simple_grouping_1) {
    ONERUT_TEST((45));
}

TEST(box_pure_integer, simple_grouping_2) {
    ONERUT_TEST(+(45));
}

TEST(box_pure_integer, simple_grouping_3) {
    ONERUT_TEST(-(45));
}

TEST(box_pure_integer, simple_grouping_4) {
    ONERUT_TEST(+(-45));
}

TEST(box_pure_integer, simple_grouping_5) {
    ONERUT_TEST(-(-45));
}

TEST(box_pure_integer, simple_grouping_6) {
    ONERUT_TEST(-((-45)));
}

TEST(box_pure_integer, simple_grouping_7) {
    BASIC_ONERUT_TEST(-((-45)), -([-45]));
}

TEST(box_pure_integer, op_plus_minus_prod_div_grouping_1) {
    ONERUT_TEST((540 * 75 * 764));
}

TEST(box_pure_integer, op_plus_minus_prod_div_grouping_2) {
    ONERUT_TEST((540 * 75) * 764);
}

TEST(box_pure_integer, op_plus_minus_prod_div_grouping_4) {
    ONERUT_TEST((540 / 75) * 764);
}

TEST(box_pure_integer, op_plus_minus_prod_div_grouping_5) {
    ONERUT_TEST(540 / (75 * 764));
}

TEST(box_pure_integer, op_plus_minus_prod_div_grouping_6) {
    ONERUT_TEST((-540 / 75) / 764);
}

//TEST(box_pure_integer, op_plus_minus_prod_div_grouping_7) {
//    ONERUT_TEST(-540 / (75 / 764));
//}

TEST(box_pure_integer, op_plus_minus_prod_div_grouping_8) {
    ONERUT_TEST((-54 - 75) * 764);
}

TEST(box_pure_integer, op_plus_minus_prod_div_grouping_9) {
    ONERUT_TEST(-54 - (75 * 764));
}

TEST(box_pure_integer, op_plus_minus_prod_div_grouping_10) {
    ONERUT_TEST(-54 / (75 + 764));
}