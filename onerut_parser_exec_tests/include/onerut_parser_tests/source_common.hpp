#ifndef ONERUT_PARSER_TEST_SOURCE_COMMON
#define ONERUT_PARSER_TEST_SOURCE_COMMON

#include<complex>
#include<memory>
#include<string>
#include<iostream>

#include<gtest/gtest.h>

#include<onerut_parser_exec/gramma_parser.hpp>
#include<onerut_parser_exec/ast_x3_to_ast_source.hpp>
#include<onerut_parser_exec/print_chart.hpp>
#include<onerut_parser_tests/global_flags.hpp>

// -----------------------------------------------------------
// ---------- API --------------------------------------------
// -----------------------------------------------------------

inline
void onerut_source_test(const std::string & _expect, const std::string onerut_inuput) {
    auto _onerut_inuput = std::make_shared<const std::string>(onerut_inuput);
    // #########################################################################
    const auto _parsed_x3_info = onerut_parser_exec::parse(_onerut_inuput);
    // --------------------------------------------------
    if (onerut_verbose) {
        std::cout << "[test][common] Parsed info (onerut_ast::x3):" << std::endl;
        print(_parsed_x3_info);
    }
    // --------------------------------------------------
    ASSERT_TRUE(_parsed_x3_info.succes());
    // #########################################################################
    const auto _ast_source_head = onerut_parser_exec::onerut_ast::to_ast_source(
            _parsed_x3_info.ast_head,
            _parsed_x3_info.input,
            _parsed_x3_info.positions);
    // --------------------------------------------------
    if (onerut_verbose) {
        const auto ast_source_ast_chart = _ast_source_head->to_ast_chart();
        onerut_parser_exec::print_ast_chart(std::cout, _parsed_x3_info.input, ast_source_ast_chart, "[test][common][source][diagram]");
    }
    // #########################################################################    
    const std::string get = _ast_source_head->to_oneliner();
    ASSERT_EQ(_expect, get);
}

#endif