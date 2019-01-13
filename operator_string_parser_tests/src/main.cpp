#include <gtest/gtest.h>
#include <operator_string_parser/parse_XXX_string.hpp>

using namespace operator_string_parser;

TEST(lstrip, test0) {
    const std::string s = "";
    const auto result = lstrip({s.cbegin(), s.cend()});
    EXPECT_EQ(string_span_to_string(result), "");
    EXPECT_EQ(result.second, s.cend());
}

TEST(lstrip, test1) {
    const std::string s = "   ";
    const auto result = lstrip({s.cbegin(), s.cend()});
    EXPECT_EQ(string_span_to_string(result), "");
    EXPECT_EQ(result.second, s.cend());
}

TEST(lstrip, test2) {
    const std::string s = "   a ";
    const auto result = lstrip({s.cbegin(), s.cend()});
    EXPECT_EQ(string_span_to_string(result), "a ");
    EXPECT_EQ(result.second, s.cend());
}

TEST(rstrip, test0) {
    const std::string s = "";
    auto result = rstrip({s.cbegin(), s.cend()});
    EXPECT_EQ(string_span_to_string(result), "");
    EXPECT_EQ(result.first, s.cbegin());
}

TEST(rstrip, test1) {
    const std::string s = "   ";
    const auto result = rstrip({s.cbegin(), s.cend()});
    EXPECT_EQ(string_span_to_string(result), "");
    EXPECT_EQ(result.first, s.cbegin());
}

TEST(rstrip, test2) {
    const std::string s = " a   ";
    const auto result = rstrip({s.cbegin(), s.cend()});
    EXPECT_EQ(string_span_to_string(result), " a");
    EXPECT_EQ(result.first, s.cbegin());
}

// #############################################################################

TEST(disregard_all_outer_nesting, test0) {
    const std::string s = "(( a  ))";
    const auto result = disregard_all_outer_nesting({s.cbegin(), s.cend()});
    EXPECT_EQ(string_span_to_string(result), " a  ");
}

TEST(disregard_all_outer_nesting, test1) {
    const std::string s = "(( a  )";
    const auto result = disregard_all_outer_nesting({s.cbegin(), s.cend()});
    EXPECT_EQ(string_span_to_string(result), "( a  ");
}

TEST(disregard_all_outer_nesting, test2) {
    const std::string s = "( a  ))";
    const auto result = disregard_all_outer_nesting({s.cbegin(), s.cend()});
    EXPECT_EQ(string_span_to_string(result), " a  )");
}

TEST(disregard_all_outer_nesting, test3) {
    const std::string s = "<(( a  ))>";
    const auto result = disregard_all_outer_nesting({s.cbegin(), s.cend()}, '<', '>');
    EXPECT_EQ(string_span_to_string(result), "(( a  ))");
}

// #############################################################################

TEST(parse_nested_comma_separated_string, test0) {
    const std::string s = "";
    const auto result = parse_nested_comma_separated_string({s.cbegin(), s.cend()});
    ASSERT_EQ(result.size(), 0);
}

TEST(parse_nested_comma_separated_string, test1) {
    const std::string s = " ";
    const auto result = parse_nested_comma_separated_string({s.cbegin(), s.cend()});
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(string_span_to_string(result[0]), " ");
}

TEST(parse_nested_comma_separated_string, test2) {
    const std::string s = "abc,de,fg";
    const auto result = parse_nested_comma_separated_string({s.cbegin(), s.cend()});
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(string_span_to_string(result[0]), "abc");
    EXPECT_EQ(string_span_to_string(result[1]), "de");
    EXPECT_EQ(string_span_to_string(result[2]), "fg");
}

TEST(parse_nested_comma_separated_string, test3) {
    const std::string s = "abc,(de,fg)";
    const auto result = parse_nested_comma_separated_string({s.cbegin(), s.cend()});
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(string_span_to_string(result[0]), "abc");
    EXPECT_EQ(string_span_to_string(result[1]), "(de,fg)");
}

TEST(parse_nested_comma_separated_string, test4) {
    const std::string s = " abc, de , fg";
    const auto result = parse_nested_comma_separated_string({s.cbegin(), s.cend()});
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(string_span_to_string(result[0]), " abc");
    EXPECT_EQ(string_span_to_string(result[1]), " de ");
    EXPECT_EQ(string_span_to_string(result[2]), " fg");
}

TEST(parse_nested_comma_separated_string, test5) {
    const std::string s = " (abc, (de)) , (fg ) ";
    const auto result = parse_nested_comma_separated_string({s.cbegin(), s.cend()});
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(string_span_to_string(result[0]), " (abc, (de)) ");
    EXPECT_EQ(string_span_to_string(result[1]), " (fg ) ");
}

TEST(parse_nested_comma_separated_string, test6) {
    const std::string s = " <abc; <de>> ; <fg >,h ";
    const auto result = parse_nested_comma_separated_string({s.cbegin(), s.cend()}, ';', '<', '>');
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(string_span_to_string(result[0]), " <abc; <de>> ");
    EXPECT_EQ(string_span_to_string(result[1]), " <fg >,h ");
}

TEST(parse_nested_comma_separated_string, test7) {
    const std::string s = " (abc, (de)) , ((fg ) ";
    EXPECT_THROW(parse_nested_comma_separated_string({s.cbegin(), s.cend()}), NestingOpenCloseCharactersMismatchError);
}

TEST(parse_nested_comma_separated_string, test8) {
    const std::string s = " (abc, (de))) , (fg ) ";
    EXPECT_THROW(parse_nested_comma_separated_string({s.cbegin(), s.cend()}), NestingOpenCloseCharactersMismatchError);
}

TEST(parse_nested_comma_separated_string, test9) {
    const std::string s = " (abc, (de)) , (fg ) ,";
    const auto result = parse_nested_comma_separated_string({s.cbegin(), s.cend()});
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(string_span_to_string(result[0]), " (abc, (de)) ");
    EXPECT_EQ(string_span_to_string(result[1]), " (fg ) ");
    EXPECT_EQ(string_span_to_string(result[2]), "");
}

TEST(parse_nested_comma_separated_string, test10) {
    const std::string s = ", (abc, (de)) , (fg ) ,";
    const auto result = parse_nested_comma_separated_string({s.cbegin(), s.cend()});
    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(string_span_to_string(result[0]), "");
    EXPECT_EQ(string_span_to_string(result[1]), " (abc, (de)) ");
    EXPECT_EQ(string_span_to_string(result[2]), " (fg ) ");
    EXPECT_EQ(string_span_to_string(result[3]), "");
}

// #############################################################################

TEST(try_parse_function, test0) {
    const std::string s = "";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_function, test1) {
    const std::string s = "foo";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(string_span_to_string(result.value().name), "foo");
    ASSERT_EQ(result.value().argv.size(), 0);
}

TEST(try_parse_function, test2) {
    const std::string s = "foo()";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(string_span_to_string(result.value().name), "foo");
    ASSERT_EQ(result.value().argv.size(), 0);
}

TEST(try_parse_function, test3) {
    const std::string s = "foo(abc,def,ghi)";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(string_span_to_string(result.value().name), "foo");
    ASSERT_EQ(result.value().argv.size(), 3);
    EXPECT_EQ(string_span_to_string(result.value().argv[0]), "abc");
    EXPECT_EQ(string_span_to_string(result.value().argv[1]), "def");
    EXPECT_EQ(string_span_to_string(result.value().argv[2]), "ghi");
}

TEST(try_parse_function, test4) {
    const std::string s = "foo((abc,def,ghi))";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(string_span_to_string(result.value().name), "foo");
    ASSERT_EQ(result.value().argv.size(), 1);
    EXPECT_EQ(string_span_to_string(result.value().argv[0]), "(abc,def,ghi)");
}

TEST(try_parse_function, test5) {
    const std::string s = "Foo_foo_123(abc,def,ghi)";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(string_span_to_string(result.value().name), "Foo_foo_123");
    ASSERT_EQ(result.value().argv.size(), 3);
    EXPECT_EQ(string_span_to_string(result.value().argv[0]), "abc");
    EXPECT_EQ(string_span_to_string(result.value().argv[1]), "def");
    EXPECT_EQ(string_span_to_string(result.value().argv[2]), "ghi");
}

TEST(try_parse_function, test6) {
    const std::string s = "(abc,def,ghi)";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_function, test7) {
    const std::string s = "*(abc,def,ghi)";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_function, test8) {
    const std::string s = ",(abc,def,ghi)";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_function, test9) {
    const std::string s = "foo(abc,def,ghi))";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_function, test10) {
    const std::string s = "foo((abc,def,ghi)";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_function, test11) {
    const std::string s = "fo!o(abc,def,ghi)";
    const auto result = try_parse_function({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

// #############################################################################

TEST(try_parse_int, test0) {
    const std::string s = "";
    const auto result = try_parse_int({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_int, test1) {
    const std::string s = "5";
    const auto result = try_parse_int({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), 5);
}

TEST(try_parse_int, test2) {
    const std::string s = "x";
    const auto result = try_parse_int({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_int, test3) {
    const std::string s = "4x";
    const auto result = try_parse_int({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_int, test4) {
    const std::string s = "1000000000000000000000000000";
    ASSERT_THROW(try_parse_int({s.cbegin(), s.cend()}), std::out_of_range);
}

// #############################################################################

TEST(try_parse_double, test0) {
    const std::string s = "";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_double, test1) {
    const std::string s = "5";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), 5.0);
}

TEST(try_parse_double, test2) {
    const std::string s = "5.0";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), 5.0);
}

TEST(try_parse_double, test3) {
    const std::string s = "+5.0";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), 5.0);
}

TEST(try_parse_double, test4) {
    const std::string s = "-5.0";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), -5.0);
}

TEST(try_parse_double, test5) {
    const std::string s = "5.";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), 5.0);
}

TEST(try_parse_double, test6) {
    const std::string s = ".5";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), 0.5);
}

TEST(try_parse_double, test7) {
    const std::string s = "5.e0";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), 5.);
}

TEST(try_parse_double, test8) {
    const std::string s = ".";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_double, test9) {
    const std::string s = "5f0";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_double, test10) {
    const std::string s = "4x";
    const auto result = try_parse_double({s.cbegin(), s.cend()});
    ASSERT_FALSE(result);
}

TEST(try_parse_double, test11) {
    const std::string s = "1e500";
    ASSERT_THROW(try_parse_double({s.cbegin(), s.cend()}), std::out_of_range);
}

// #############################################################################

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
