#include<limits>
#include<memory>
#include<string>
#include<type_traits>

#include<gtest/gtest.h>

#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_dyn.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_scalar/scalar.hpp>

//#include<esc/esc_manip.hpp>


const bool test_verbose = true;
//template<typename T1,typename T2>
//bool _is_a_given_type(T1 v){
//    return  std::is_same<T1, T2>::value;
//}

const double inf = std::numeric_limits<double>::infinity();

TEST(test_suite, test0) {
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
    EXPECT_EQ(7, 7);
    EXPECT_EQ(inf, inf);
}

template<typename T>
void _basis_onerut_test(T _cpp_value, std::shared_ptr<std::u32string> _onerut_inuput);


#define BASIC_ONERUT_TEST(CPP_EXPRESSION, ONERUT_EXPRESSION)  \
std::cout << "[test][common] cpp_expression:" << (#CPP_EXPRESSION) << std::endl; \
auto _cpp_value = CPP_EXPRESSION; \
auto _onerut_inuput = std::make_shared<std::u32string>(U ## #ONERUT_EXPRESSION); \
_basis_onerut_test(_cpp_value, _onerut_inuput);
//auto _onerut_inuput = std::make_shared<std::u32string>(U#ONERUT_EXPRESSION); 


template<typename T>
void _basis_onerut_test(T _cpp_value, std::shared_ptr<std::u32string> _onerut_inuput) {
    std::cout << "[test][common] cpp_value: " << _cpp_value << std::endl;
    bool _cpp_is_int = std::is_same < decltype(_cpp_value), int>::value;
    bool _cpp_is_double = std::is_same < decltype(_cpp_value), double>::value;
    if (test_verbose) {
        std::cout << "[test][common] cpp_is_int: " << _cpp_is_int << std::endl;
        std::cout << "[test][common] cpp_is_double: " << _cpp_is_double << std::endl;
    }
    // --------------------------------------------------
    const auto _parsed_x3_info = onerut_parser::parse(_onerut_inuput);
    if (test_verbose) {
        std::cout << "[test][common] Parsed info (onerut_ast::x3):" << std::endl;
        print(_parsed_x3_info);
    }
    // --------------------------------------------------
    const auto _ast_dyn_head = onerut_parser::onerut_ast::to_ast_dyn(
            _parsed_x3_info.ast_head,
            _parsed_x3_info.input,
            _parsed_x3_info.positions);
    if (test_verbose) {
        std::cout << "[test][common] Parsed info (onerut_ast::dyn):" << std::endl;
        const auto ast_dyn_chart = _ast_dyn_head->to_chart();
        onerut_parser::print_chart(_parsed_x3_info.input, ast_dyn_chart);
    }
    // -------------------------------------------------------------------------
    onerut_parser::BuildResult _result = _ast_dyn_head->build();
    if (test_verbose) {
        if (_result.is_error()) {
            std::cout << "[test][common] (onerut_ast::dyn) onerut expression is an error." << std::endl;
            std::cout << (*_result.build_error_or_empty())->what() << std::endl;
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
    ASSERT_TRUE(!_result.is_error()); // bedzie is_value_or_type
    ASSERT_EQ(_cpp_is_int, _result.is_given_type<onerut_scalar::Long>());
    ASSERT_EQ(_cpp_is_double, _result.is_given_type<onerut_scalar::Double>());
    if (_cpp_is_int) {
        std::shared_ptr<onerut_scalar::Long> result_long = *(_result.typed_value_or_empty<onerut_scalar::Long>());
        long _onerut_value = result_long->value_long();
        EXPECT_EQ(_cpp_value, _onerut_value);
    }
    if (_cpp_is_double) {
        std::shared_ptr<onerut_scalar::Double> result_double = *(_result.typed_value_or_empty<onerut_scalar::Double>());
        long _onerut_value = result_double->value_double();
        EXPECT_EQ(_cpp_value, _onerut_value);
    }

} // end function

TEST(test_suite, test1) {


    //std::cout << "[test][common] cpp_expression:" << (#CPPEPRESSION) << std::endl;
    auto _cpp_value = 44.;
    std::cout << "[test][common] cpp_value: " << _cpp_value << std::endl;
    bool _cpp_is_int = std::is_same < decltype(_cpp_value), int>::value;
    bool _cpp_is_double = std::is_same < decltype(_cpp_value), double>::value;
    if (test_verbose) {
        std::cout << "[test][common] cpp_is_int: " << _cpp_is_int << std::endl;
        std::cout << "[test][common] cpp_is_double: " << _cpp_is_double << std::endl;
    }
    // --------------------------------------------------
    auto _onerut_inuput = std::make_shared<std::u32string>(U"44.");
    const auto _parsed_x3_info = onerut_parser::parse(_onerut_inuput);
    if (test_verbose) {
        std::cout << "[test][common] Parsed info (onerut_ast::x3):" << std::endl;
        print(_parsed_x3_info);
    }
    // -------------------------------------------------------------------------
    const auto _ast_dyn_head = onerut_parser::onerut_ast::to_ast_dyn(
            _parsed_x3_info.ast_head,
            _parsed_x3_info.input,
            _parsed_x3_info.positions);
    if (test_verbose) {
        std::cout << "[test][common] Parsed info (onerut_ast::dyn):" << std::endl;
        const auto ast_dyn_chart = _ast_dyn_head->to_chart();
        onerut_parser::print_chart(_parsed_x3_info.input, ast_dyn_chart);
    }
    // -------------------------------------------------------------------------
    onerut_parser::BuildResult _result = _ast_dyn_head->build();
    if (test_verbose) {
        if (_result.is_error()) {
            std::cout << "[test][common] (onerut_ast::dyn) onerut expression is an error." << std::endl;
            std::cout << (*_result.build_error_or_empty())->what() << std::endl;
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
    ASSERT_TRUE(!_result.is_error()); // bedzie is_value_or_type
    ASSERT_EQ(_cpp_is_int, _result.is_given_type<onerut_scalar::Long>());
    ASSERT_EQ(_cpp_is_double, _result.is_given_type<onerut_scalar::Double>());
    if (_cpp_is_int) {
        std::shared_ptr<onerut_scalar::Long> result_long = *(_result.typed_value_or_empty<onerut_scalar::Long>());
        long _onerut_value_long = result_long->value_long();
        EXPECT_EQ(_cpp_value, _onerut_value_long);
    }
    if (_cpp_is_double) {

        std::shared_ptr<onerut_scalar::Double> result_double = *(_result.typed_value_or_empty<onerut_scalar::Double>());
        long _onerut_value_double = result_double->value_double();
        EXPECT_EQ(_cpp_value, _onerut_value_double);
    }

}

TEST(test_suite, test2) {
    BASIC_ONERUT_TEST(45, 65);
}
//    std::string input = "10000000000000000+1.";
//    std::string input = "10000000000000000+1";
