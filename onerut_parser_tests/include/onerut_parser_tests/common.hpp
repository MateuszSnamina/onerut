#ifndef ONERUT_PARSER_TEST_COMMON
#define ONERUT_PARSER_TEST_COMMON

#include<limits>
#include<memory>
#include<string>
#include<type_traits>

#include<gtest/gtest.h>

#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_dyn.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_scalar/scalar.hpp>
#include<onerut_parser_tests/global_flags.hpp>

// -----------------------------------------------------------
// ---------- API --------------------------------------------
// -----------------------------------------------------------

const double inf = std::numeric_limits<double>::infinity();

template<typename T>
void _basis_onerut_test(T _cpp_value, std::shared_ptr<std::u32string> _onerut_inuput);

#define BASIC_ONERUT_TEST(CPP_EXPRESSION, ONERUT_EXPRESSION)                     \
std::cout << "[test][common] cpp_expression:" << (#CPP_EXPRESSION) << std::endl; \
auto _cpp_value = CPP_EXPRESSION;                                                \
auto _onerut_inuput = std::make_shared<std::u32string>(U ## #ONERUT_EXPRESSION); \
_basis_onerut_test(_cpp_value, _onerut_inuput);

#define ONERUT_TEST(EXPRESSION)  \
BASIC_ONERUT_TEST(EXPRESSION, EXPRESSION)

// -----------------------------------------------------------
// ---------- TEMPLATE FUNCTIONS IMPLEMENTATION --------------
// -----------------------------------------------------------

template<typename T>
void _basis_onerut_test(T _cpp_value, std::shared_ptr<std::u32string> _onerut_inuput) {
    // --------------------------------------------------    
    std::cout << "[test][common] cpp_value: " << _cpp_value << std::endl;
    bool _cpp_is_int =
            std::is_same < decltype(_cpp_value), long>::value ||
            std::is_same < decltype(_cpp_value), int>::value;
    bool _cpp_is_double =
            std::is_same < decltype(_cpp_value), double>::value;
    if (onerut_verbose) {
        std::cout << "[test][common] cpp_is_int: " << _cpp_is_int << std::endl;
        std::cout << "[test][common] cpp_is_double: " << _cpp_is_double << std::endl;
    }
    // --------------------------------------------------
    // --------------------------------------------------
    const auto _parsed_x3_info = onerut_parser::parse(_onerut_inuput);
    // --------------------------------------------------
    if (onerut_verbose) {
        std::cout << "[test][common] Parsed info (onerut_ast::x3):" << std::endl;
        print(_parsed_x3_info);
    }
    // --------------------------------------------------
    ASSERT_TRUE(_parsed_x3_info.succes());
    // --------------------------------------------------
    const auto _ast_dyn_head = onerut_parser::onerut_ast::to_ast_dyn(
            _parsed_x3_info.ast_head,
            _parsed_x3_info.input,
            _parsed_x3_info.positions);
    // --------------------------------------------------
    if (onerut_verbose) {
        std::cout << "[test][common] Parsed info (onerut_ast::dyn):" << std::endl;
        const auto ast_dyn_chart = _ast_dyn_head->to_chart();
        onerut_parser::print_chart(_parsed_x3_info.input, ast_dyn_chart);
    }
    // -------------------------------------------------------------------------
    // --------------------------------------------------    
    onerut_parser::CompileResult _result = _ast_dyn_head->compile();
    // --------------------------------------------------    
    if (onerut_verbose) {
        if (_result.is_compile_error()) {
            std::cout << "[test][common] (onerut_ast::dyn) onerut expression is an error." << std::endl;
            std::cout << (*_result.compile_error_or_empty())->what() << std::endl;
        } else if (_result.is_given_type<onerut_scalar::Long>()) {
            std::cout << "[test][common] (onerut_ast::dyn) onerut expression is an int." << std::endl;
            std::shared_ptr<onerut_scalar::Long> result_long = *(_result.typed_value_or_empty<onerut_scalar::Long>());
            std::cout << "[test][common] (onerut_ast::dyn) onerut_value = " << result_long->value_long() << std::endl;
        } else if (_result.is_given_type<onerut_scalar::Double>()) {
            std::cout << "[test][common] (onerut_ast::dyn) onerut expression is double." << std::endl;
            std::shared_ptr<onerut_scalar::Double> result_double = *(_result.typed_value_or_empty<onerut_scalar::Double>());
            std::cout << std::setprecision(20); //TODO
            std::cout << "[test][common] (onerut_ast::dyn) onerut_value = " << result_double->value_double() << std::endl;
        } else {
            std::cout << "[test][common] (onerut_ast::dyn) NOT INT NOR DOUBLE" << std::endl;
        }
    }
    // --------------------------------------------------    
    // --------------------------------------------------    
    ASSERT_TRUE(!_result.is_compile_error()); // bedzie is_value_or_type
    ASSERT_EQ(_cpp_is_int, _result.is_given_type<onerut_scalar::Long>());
    ASSERT_EQ(_cpp_is_double, _result.is_given_type<onerut_scalar::Double>());
    if (_cpp_is_int) {
        std::shared_ptr<onerut_scalar::Long> result_long = *(_result.typed_value_or_empty<onerut_scalar::Long>());
        long _onerut_value = result_long->value_long();
        EXPECT_EQ(_cpp_value, _onerut_value);
    }
    if (_cpp_is_double) {
        std::shared_ptr<onerut_scalar::Double> result_double = *(_result.typed_value_or_empty<onerut_scalar::Double>());
        double _onerut_value = result_double->value_double();
        EXPECT_EQ(_cpp_value, _onerut_value);
    }

}

#endif
