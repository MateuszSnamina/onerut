#ifndef ONERUT_PARSER_TEST_COMMON
#define ONERUT_PARSER_TEST_COMMON

#include<limits>
#include<memory>
#include<optional>
#include<string>
#include<complex>

#include<gtest/gtest.h>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_source.hpp>
#include<onerut_parser/ast_asset.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/asset_receipt.hpp>
#include<onerut_parser/function_factory_container.hpp>
#include<onerut_parser_tests/global_flags.hpp>

using namespace std::complex_literals;

// -----------------------------------------------------------
// ---------- API --------------------------------------------
// -----------------------------------------------------------

const double inf = std::numeric_limits<double>::infinity();

inline
void onerut_source_test(const std::string & _expect, const std::string onerut_inuput) {
    auto _onerut_inuput = std::make_shared<const std::string>(onerut_inuput);
    // #########################################################################
    const auto _parsed_x3_info = onerut_parser::parse(_onerut_inuput);
    // --------------------------------------------------
    if (onerut_verbose) {
        std::cout << "[test][common] Parsed info (onerut_ast::x3):" << std::endl;
        print(_parsed_x3_info);
    }
    // --------------------------------------------------
    ASSERT_TRUE(_parsed_x3_info.succes());
    // #########################################################################
    const auto _ast_source_head = onerut_parser::onerut_ast::to_ast_source(
            _parsed_x3_info.ast_head,
            _parsed_x3_info.input,
            _parsed_x3_info.positions);
    // --------------------------------------------------
    if (onerut_verbose) {
        const auto ast_source_ast_chart = _ast_source_head->to_ast_chart();
        onerut_parser::print_ast_chart(std::cout, _parsed_x3_info.input, ast_source_ast_chart, "[test][common][source][diagram]");
    }
    // #########################################################################    
    const std::string _got = _ast_source_head->to_oneliner();
    ASSERT_EQ(_expect, _got);
}


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

inline
std::optional<onerut_parser::Asset> onerut_inuput_2_asset(const std::string onerut_inuput) {
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    auto _onerut_inuput = std::make_shared<const std::string>(onerut_inuput);
    // #########################################################################
    const auto _parsed_x3_info = onerut_parser::parse(_onerut_inuput);
    // --------------------------------------------------
    if (onerut_verbose) {
        std::cout << "[test][common] Parsed info (onerut_ast::x3):" << std::endl;
        print(_parsed_x3_info);
    }
    // --------------------------------------------------
    if (!_parsed_x3_info.succes())
        return std::nullopt;
    // #########################################################################
    const auto _ast_source_head = onerut_parser::onerut_ast::to_ast_source(
            _parsed_x3_info.ast_head,
            _parsed_x3_info.input,
            _parsed_x3_info.positions);
    // --------------------------------------------------
    if (onerut_verbose) {
        const auto ast_source_ast_chart = _ast_source_head->to_ast_chart();
        onerut_parser::print_ast_chart(std::cout, _parsed_x3_info.input, ast_source_ast_chart, "[test][common][source][diagram]");
    }
    // #########################################################################
    const auto _ast_asset_head = _ast_source_head->compile();
    // -------------------------------------------------------------------------
    if (onerut_verbose) {
        const auto ast_asset_ast_chart = _ast_asset_head->to_ast_chart();
        onerut_parser::print_ast_chart(std::cout, _parsed_x3_info.input, ast_asset_ast_chart, "[test][common][asset][diagram]");
    }
    // #########################################################################
    onerut_parser::Asset _asset = _ast_asset_head->asset;
    // --------------------------------------------------    
    if (onerut_verbose)
        onerut_parser::print_receipt(std::cout, _asset, "[test][common] ");
    // --------------------------------------------------    
    return _asset;
}

template<class T>
struct BasisOnerutTest {
};

template<>
struct BasisOnerutTest<std::complex<double> > {

    static void test(std::complex<double> cpp_value, const std::string onerut_inuput) {
        std::cout << "[test][common] cpp is complex." << std::endl;
        const auto _asset = onerut_inuput_2_asset(onerut_inuput);
        ASSERT_TRUE(_asset);
        ASSERT_TRUE(!_asset->deref().is_compile_error()); // TODO bedzie is_value_or_type
        const auto result_complex = _asset->deref().typed_value_or_empty<onerut_scalar::Complex>();
        ASSERT_TRUE(result_complex);
        const auto onerut_value = (*result_complex)->value_complex();
        EXPECT_EQ(cpp_value, onerut_value);
    }
};

template<>
struct BasisOnerutTest<double> {

    static void test(double cpp_value, const std::string onerut_inuput) {
        std::cout << "[test][common] cpp is real." << std::endl;
        const auto _asset = onerut_inuput_2_asset(onerut_inuput);
        ASSERT_TRUE(_asset);
        ASSERT_TRUE(!_asset->deref().is_compile_error()); // TODO bedzie is_value_or_type
        const auto result_complex = _asset->deref().typed_value_or_empty<onerut_scalar::Real>();
        ASSERT_TRUE(result_complex);
        const auto onerut_value = (*result_complex)->value_real();
        EXPECT_EQ(cpp_value, onerut_value);
    }
};

template<>
struct BasisOnerutTest<long> {

    static void test(long cpp_value, const std::string onerut_inuput) {
        const auto _asset = onerut_inuput_2_asset(onerut_inuput);
        ASSERT_TRUE(_asset);
        ASSERT_TRUE(!_asset->deref().is_compile_error()); // TODO bedzie is_value_or_type
        const auto result_integer = _asset->deref().typed_value_or_empty<onerut_scalar::Integer>();
        ASSERT_TRUE(result_integer);
        const auto onerut_value = (*result_integer)->value_integer();
        EXPECT_EQ(cpp_value, onerut_value);
    }
};

template<typename T>
void basis_onerut_test(T cpp_value, const std::string onerut_inuput) {
    using Type = typename PromotedType<T>::Type;
    BasisOnerutTest<Type>::test(cpp_value, onerut_inuput);
}

#endif
