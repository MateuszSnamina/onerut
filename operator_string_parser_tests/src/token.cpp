#include <gtest/gtest.h>
#include "operator_string_parser/token.hpp"

using namespace operator_string_parser;

// #############################################################################

TEST(try_get_int_token, test0) {
    const std::string s = "";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_int_token, test1) {
    const std::string s = " ";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_int_token, test2) {
    const std::string s = "a";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_int_token, test3) {
    const std::string s = "+";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_int_token, test4) {
    const std::string s = "-";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_int_token, test5) {
    const std::string s = "7 ";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, 7);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 1);
}

TEST(try_get_int_token, test6) {
    const std::string s = "78 ";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, 78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 2);
}

TEST(try_get_int_token, test7) {
    const std::string s = "+78 ";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, +78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_int_token, test8) {
    const std::string s = "-78" ;
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_int_token, test9) {
    const std::string s = "+78e ";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, +78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_int_token, test10) {
    const std::string s = "-78e ";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_int_token, test11) {
    const std::string s = "-1.0 ";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -1);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 2);
}

TEST(try_get_int_token, test12) {
    const std::string s = "x5";
    const auto resut = try_get_int_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

//##############################################################################

TEST(try_get_double_token, test0) {
    const std::string s = "";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_double_token, test1) {
    const std::string s = " ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_double_token, test2) {
    const std::string s = "a";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_double_token, test3) {
    const std::string s = "+";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_double_token, test4) {
    const std::string s = "-";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_double_token, test5) {
    const std::string s = "7 ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, 7);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 1);
}

TEST(try_get_double_token, test6) {
    const std::string s = "78 ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, 78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 2);
}

TEST(try_get_double_token, test7) {
    const std::string s = "+78 ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, +78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_double_token, test8) {
    const std::string s = "-78 ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_double_token, test9) {
    const std::string s = "-1.5 ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -1.5);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 4);
}

TEST(try_get_double_token, test10) {
    const std::string s = "-7.";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -7.0);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_double_token, test11) {
    const std::string s = "-.4";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -0.4);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_double_token, test12) {
    const std::string s = ".";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_double_token, test13) {
    const std::string s = "+78e";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, +78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_double_token, test14) {
    const std::string s = "-78e";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -78);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 3);
}

TEST(try_get_double_token, test15) {
    const std::string s = "-1.3e  ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -1.3);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 4);    
}

TEST(try_get_double_token, test16) {
    const std::string s = "-1.3e5 ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -1.3e5);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 6);
}

TEST(try_get_double_token, test17) {
    const std::string s = "-1.7e+5 ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -1.7e+5);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 7);
}

TEST(try_get_double_token, test18) {
    const std::string s = "-1.9e-5";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -1.9e-5);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 7);
}

TEST(try_get_double_token, test19) {
    const std::string s = "-.2e-5 ";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, -.2e-5);
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 6);
}

TEST(try_get_double_token, test20) {
    const std::string s = "x5";
    const auto resut = try_get_double_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}
//##############################################################################

TEST(try_get_string_token, test0) {
    const std::string s = R"()";
    const auto resut = try_get_string_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_string_token, test1) {
    const std::string s = R"(x"ala")";
    const auto resut = try_get_string_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_string_token, test2) {
    const std::string s = R"(")";
    const auto resut = try_get_string_token({s.cbegin(), s.cend()});
    ASSERT_FALSE(resut);
}

TEST(try_get_string_token, test3) {
    const std::string s = R"("ala" )";
    const auto resut = try_get_string_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, R"(ala)");
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 5);
}

TEST(try_get_string_token, test4) {
    const std::string s = R"("a\"la" )";
    const auto resut = try_get_string_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, R"(a"la)");
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 7);
}

TEST(try_get_string_token, test5) {
    const std::string s = R"("ala" "ola")";
    const auto resut = try_get_string_token({s.cbegin(), s.cend()});
    ASSERT_TRUE(resut);
    EXPECT_EQ(resut->value, R"(ala)");
    EXPECT_EQ(resut->span.begin(), s.cbegin());
    EXPECT_EQ(resut->span.end(), s.cbegin() + 5);
}
//##############################################################################
