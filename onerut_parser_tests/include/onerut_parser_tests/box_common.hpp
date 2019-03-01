#ifndef ONERUT_PARSER_TEST_BOX_COMMON
#define ONERUT_PARSER_TEST_BOX_COMMON

#include<limits>
#include<memory>
#include<optional>
#include<string>
#include<complex>

#include<gtest/gtest.h>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_parser/ast_asset.hpp>
#include<onerut_parser/function_factory_container.hpp>
#include<onerut_parser_tests/global_flags.hpp>
#include<onerut_parser_tests/inuput_2_asset.hpp>

// -----------------------------------------------------------
// ---------- API --------------------------------------------
// -----------------------------------------------------------

using namespace std::complex_literals;
const double inf = std::numeric_limits<double>::infinity();

template<typename T>
void basis_onerut_test(T cpp_value, const std::string onerut_inuput);

#define BASIC_ONERUT_TEST(CPP_EXPRESSION, ONERUT_EXPRESSION)                     \
std::cout << "[test][common] cpp_expression    : " << (#CPP_EXPRESSION) << std::endl; \
std::cout << "[test][common] onerut_expression : " << (#ONERUT_EXPRESSION) << std::endl; \
basis_onerut_test(CPP_EXPRESSION, #ONERUT_EXPRESSION);

#define ONERUT_TEST(EXPRESSION)  \
BASIC_ONERUT_TEST(EXPRESSION, EXPRESSION)

// -----------------------------------------------------------
// ---------- TEMPLATE FUNCTIONS IMPLEMENTATION --------------
// -----------------------------------------------------------

template<class T>
struct PromotedType {
};

template<>
struct PromotedType<long> {
    using Type = long;
};

template<>
struct PromotedType<int> {
    using Type = long;
};

template<>
struct PromotedType<double> {
    using Type = double;
};

template<>
struct PromotedType<std::complex<double> > {
    using Type = std::complex<double>;
};

//------------------------------------------------------------------------------

template<class T>
struct BasisOnerutTest {
};

template<>
struct BasisOnerutTest<std::complex<double> > {

    static void test(
            const std::complex<double> &cpp_value,
            const onerut_parser::Asset& asset) {
        std::cout << "[test][common] complex numbers comparison test." << std::endl;
        ASSERT_TRUE(!asset.deref().is_compile_error());
        ASSERT_TRUE(!asset.deref().is_empty());
        const auto result_complex = asset.deref().typed_value_or_empty<onerut_scalar::Complex>();
        ASSERT_TRUE(result_complex);
        const auto onerut_value = (*result_complex)->value_complex();
        std::cout << "[test][common] cpp_value    : " << cpp_value << std::endl;
        std::cout << "[test][common] onerut_value : " << onerut_value << std::endl;
        EXPECT_EQ(cpp_value, onerut_value);
    }
};

template<>
struct BasisOnerutTest<double> {

    static void test(
            double cpp_value,
            const onerut_parser::Asset& asset) {
        std::cout << "[test][common] real numbers comparison test." << std::endl;
        ASSERT_TRUE(!asset.deref().is_compile_error());
        ASSERT_TRUE(!asset.deref().is_empty());
        const auto result_complex = asset.deref().typed_value_or_empty<onerut_scalar::Real>();
        ASSERT_TRUE(result_complex);
        const auto onerut_value = (*result_complex)->value_real();
        std::cout << "[test][common] cpp_value    : " << cpp_value << std::endl;
        std::cout << "[test][common] onerut_value : " << onerut_value << std::endl;
        EXPECT_EQ(cpp_value, onerut_value);
    }
};

template<>
struct BasisOnerutTest<long> {

    static void test(
            long cpp_value,
            const onerut_parser::Asset& asset) {
        std::cout << "[test][common] integer numbers comparison test." << std::endl;
        ASSERT_TRUE(!asset.deref().is_compile_error());
        ASSERT_TRUE(!asset.deref().is_empty());
        const auto result_integer = asset.deref().typed_value_or_empty<onerut_scalar::Integer>();
        ASSERT_TRUE(result_integer);
        const auto onerut_value = (*result_integer)->value_integer();
        std::cout << "[test][common] cpp_value    : " << cpp_value << std::endl;
        std::cout << "[test][common] onerut_value : " << onerut_value << std::endl;
        EXPECT_EQ(cpp_value, onerut_value);
    }
};

//------------------------------------------------------------------------------

template<typename T>
void basis_onerut_test(T cpp_value, const std::string onerut_inuput) {
    //----
    const auto asset = inuput_2_asset(onerut_inuput);
    ASSERT_TRUE(asset);
    //----
    using Type = typename PromotedType<T>::Type;
    BasisOnerutTest<Type>::test(cpp_value, *asset);
}

#endif