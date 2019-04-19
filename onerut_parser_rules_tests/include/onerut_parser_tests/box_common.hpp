#ifndef ONERUT_PARSER_TEST_BOX_COMMON
#define ONERUT_PARSER_TEST_BOX_COMMON

#include<limits>
#include<memory>
#include<optional>
#include<complex>
#include<string>
#include<iostream>
#include<iomanip>


#include<gtest/gtest.h>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_parser_exec/asset_error.hpp>
#include<onerut_parser_exec/ast_asset.hpp>
#include<onerut_parser_tests/global_flags.hpp>
#include<onerut_parser_tests/inuput_2_asset.hpp>

// -----------------------------------------------------------
// ---------- API --------------------------------------------
// -----------------------------------------------------------

using namespace std; //to allow CPP_EXPRESSION such as abs(4.5).
using namespace std::complex_literals; //to allow CPP_EXPRESSION such as 5i.
const double inf = std::numeric_limits<double>::infinity(); //to allow CPP_EXPRESSION containing inf.

template<typename T>
void onerut_box_value_test(T cpp_value, const std::string onerut_inuput);

#define BASIC_ONERUT_BOX_VALUE_TEST(CPP_EXPRESSION, ONERUT_EXPRESSION)                     \
  std::cout << "[test][common] cpp_expression    : " << (#CPP_EXPRESSION) << std::endl; \
  std::cout << "[test][common] onerut_expression : " << (#ONERUT_EXPRESSION) << std::endl; \
  onerut_box_value_test(CPP_EXPRESSION, #ONERUT_EXPRESSION);

#define ONERUT_BOX_VALUE_TEST(EXPRESSION)  \
  BASIC_ONERUT_BOX_VALUE_TEST(EXPRESSION, EXPRESSION)


#define ONERUT_BOX_ERROR_TEST(ERROR, EXPRESSION)  \
 onerut_box_error_test<onerut_parser_exec::ERROR>(#EXPRESSION);

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
struct ValueTest {
};

template<>
struct ValueTest<std::complex<double> > {
    static void test(
            const std::complex<double> &cpp_value,
            const onerut_parser_exec::Asset& asset);
};

template<>
struct ValueTest<double> {
    static void test(
            double cpp_value,
            const onerut_parser_exec::Asset& asset);
};

template<>
struct ValueTest<long> {
    static void test(
            long cpp_value,
            const onerut_parser_exec::Asset& asset);
};

inline
void ValueTest<std::complex<double> >::test(
        const std::complex<double> &cpp_value,
        const onerut_parser_exec::Asset& asset) {
    std::cout << "[test][common] complex numbers comparison test." << std::endl;
    ASSERT_TRUE(!asset.deref().is_compile_error()) << "Expected an asset being a value asset.";
    ASSERT_TRUE(!asset.deref().is_empty()) << "Expected an asset being a value asset.";
    const auto result_complex = asset.deref().typed_value_or_empty<onerut_scalar::Complex>();
    ASSERT_TRUE(result_complex) << "Expected an asset being a complex number.";
    const auto onerut_value = (*result_complex)->value_complex();
    std::cout << "[test][common] cpp_value    : " << cpp_value << std::endl;
    std::cout << "[test][common] onerut_value : " << onerut_value << std::endl;
    if (!std::isnan(real(cpp_value)) || !std::isnan(real(onerut_value))) {
        ASSERT_DOUBLE_EQ(real(cpp_value), real(onerut_value)) << "Comparison of real part of the numbers failed.";
    }
    if (!std::isnan(imag(cpp_value)) || !std::isnan(imag(onerut_value))) {
        ASSERT_DOUBLE_EQ(imag(cpp_value), imag(onerut_value)) << "Comparison of imag part of the numbers failed.";
    }
}

inline
void ValueTest<double>::test(
        double cpp_value,
        const onerut_parser_exec::Asset& asset) {
    std::cout << "[test][common] real numbers comparison test." << std::endl;
    ASSERT_TRUE(!asset.deref().is_compile_error()) << "Expected an asset being a value asset.";
    ASSERT_TRUE(!asset.deref().is_empty()) << "Expected an asset being a value asset.";
    const auto result_complex = asset.deref().typed_value_or_empty<onerut_scalar::Real>();
    ASSERT_TRUE(result_complex) << "Expected an asset being a real number.";
    const auto onerut_value = (*result_complex)->value_real();
    const auto stream_flags = std::cout.flags();
    std::cout << std::setprecision(18);
    std::cout << "[test][common] cpp_value    : " << cpp_value << std::endl;
    std::cout << "[test][common] onerut_value : " << onerut_value << std::endl;
    std::cout.flags(stream_flags);
    if (!std::isnan(cpp_value) || !std::isnan(onerut_value)) {
        ASSERT_DOUBLE_EQ(cpp_value, onerut_value) << "Comparison (double-eq) of the numbers failed.";
    }
}

inline
void ValueTest<long>::test(
        long cpp_value,
        const onerut_parser_exec::Asset& asset) {
    std::cout << "[test][common] integer numbers comparison test." << std::endl;
    ASSERT_TRUE(!asset.deref().is_compile_error()) << "Expected an asset being a value asset.";
    ASSERT_TRUE(!asset.deref().is_empty()) << "Expected an asset being a value asset.";
    const auto result_integer = asset.deref().typed_value_or_empty<onerut_scalar::Integer>();
    ASSERT_TRUE(result_integer) << "Expected an asset being an integer number.";
    const auto onerut_value = (*result_integer)->value_integer();
    std::cout << "[test][common] cpp_value    : " << cpp_value << std::endl;
    std::cout << "[test][common] onerut_value : " << onerut_value << std::endl;
    EXPECT_EQ(cpp_value, onerut_value) << "Comparison (long-eq) of the numbers failed.";
}


//------------------------------------------------------------------------------

template<typename T>
void onerut_box_value_test(T cpp_value, const std::string onerut_inuput) {
    const auto asset = inuput_2_asset(onerut_inuput);
    ASSERT_TRUE(asset) << "Expected an input with no grammar errors." << " Input: " << onerut_inuput;;
    //----
    using Type = typename PromotedType<T>::Type;
    ValueTest<Type>::test(cpp_value, *asset);
}

template<typename T>
void onerut_box_error_test(const std::string onerut_inuput) {
    const auto asset = inuput_2_asset(onerut_inuput);
    ASSERT_TRUE(asset) << "Expected an input with no grammar errors." << " Input: " << onerut_inuput;
    //----
    ASSERT_TRUE(!asset->deref().is_either_value_or_type()) << "Expected an asset being a compile error asset." << " Input: " << onerut_inuput;
    ASSERT_TRUE(!asset->deref().is_empty()) << "Expected an asset being a compile error asset." << " Input: " << onerut_inuput;
    ASSERT_TRUE(asset->deref().is_compile_error()) << "Expected an asset being a compile error asset." << " Input: " << onerut_inuput;
    const auto error = asset->deref().compile_error_or_empty();
    ASSERT_TRUE(error) << "Expected an asset being a compile error asset." << " Input: " << onerut_inuput;
    const auto error_casted = std::dynamic_pointer_cast<const T>(*error);
    ASSERT_TRUE(error_casted) << "Expected an asset being an error of different type." << " Input: " << onerut_inuput;
}


#endif