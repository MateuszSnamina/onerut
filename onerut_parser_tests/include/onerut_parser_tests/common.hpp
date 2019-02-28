#ifndef ONERUT_PARSER_TEST_COMMON
#define ONERUT_PARSER_TEST_COMMON

#include<limits>
#include<memory>
#include<string>
#include<type_traits>

#include<gtest/gtest.h>

#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_source.hpp>
#include<onerut_parser/ast_asset.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/asset_receipt.hpp>
#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_parser_tests/global_flags.hpp>

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
std::cout << "[test][common] cpp_expression:" << (#CPP_EXPRESSION) << std::endl; \
auto _cpp_value = CPP_EXPRESSION;                                                \
basis_onerut_test(_cpp_value, #ONERUT_EXPRESSION);

#define ONERUT_TEST(EXPRESSION)  \
BASIC_ONERUT_TEST(EXPRESSION, EXPRESSION)


// -----------------------------------------------------------
// ---------- TEMPLATE FUNCTIONS IMPLEMENTATION --------------
// -----------------------------------------------------------

template<typename T>
void basis_onerut_test(T cpp_value, const std::string onerut_inuput) {
    auto _onerut_inuput = std::make_shared<const std::string>(onerut_inuput);
    // #########################################################################
    std::cout << "[test][common] cpp_value: " << cpp_value << std::endl;
    bool _cpp_is_int =
            std::is_same < decltype(cpp_value), long>::value ||
            std::is_same < decltype(cpp_value), int>::value;
    bool _cpp_is_double =
            std::is_same < decltype(cpp_value), double>::value;
    if (onerut_verbose) {
        std::cout << "[test][common] cpp_is_int: " << _cpp_is_int << std::endl;
        std::cout << "[test][common] cpp_is_double: " << _cpp_is_double << std::endl;
    }
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
    const auto _ast_asset_head = _ast_source_head->compile();
    // -------------------------------------------------------------------------
    const auto ast_asset_ast_chart = _ast_asset_head->to_ast_chart();
    onerut_parser::print_ast_chart(std::cout, _parsed_x3_info.input, ast_asset_ast_chart, "[test][common][asset][diagram]");
    // #########################################################################
    onerut_parser::Asset _asset = _ast_asset_head->asset;
    // --------------------------------------------------    
    if (onerut_verbose)
        onerut_parser::print_receipt(std::cout, _asset, "[test][common] ");
    // --------------------------------------------------    
    // --------------------------------------------------    
    ASSERT_TRUE(!_asset.deref().is_compile_error()); // bedzie is_value_or_type
    ASSERT_EQ(_cpp_is_int, _asset.deref().is_given_type<onerut_scalar::Integer>());
    ASSERT_EQ(_cpp_is_double, _asset.deref().is_given_type<onerut_scalar::Real>());
    if (_cpp_is_int) {
        std::shared_ptr<onerut_scalar::Integer> result_integer = *(_asset.deref().typed_value_or_empty<onerut_scalar::Integer>());
        auto _onerut_value = result_integer->value_integer();
        EXPECT_EQ(cpp_value, _onerut_value);
    }
    if (_cpp_is_double) {
        std::shared_ptr<onerut_scalar::Real> result_real = *(_asset.deref().typed_value_or_empty<onerut_scalar::Real>());
        auto _onerut_value = result_real->value_real();
        EXPECT_EQ(cpp_value, _onerut_value);
    }

}

#endif
