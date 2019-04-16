#ifndef ONERUT_PARSER_TEST_INPUT_2_ASSET
#define ONERUT_PARSER_TEST_INPUT_2_ASSET

#include<memory>
#include<optional>
#include<string>
#include<complex>

#include<gtest/gtest.h>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_parser_exec/gramma_parser.hpp>
#include<onerut_parser_exec/ast_x3_to_ast_source.hpp>
#include<onerut_parser_exec/ast_asset.hpp>
#include<onerut_parser_exec/print_chart.hpp>
#include<onerut_parser_rules/asset_receipt.hpp>
#include<onerut_parser_rules/compiler_rules_concrete.hpp>
#include<onerut_parser_rules/asset_to_esc_data.hpp>
#include<onerut_parser_tests/global_flags.hpp>

inline
std::optional<onerut_parser::Asset> inuput_2_asset(const std::string onerut_inuput) {
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
    const auto _ast_asset_head = _ast_source_head->compile(std::make_shared<onerut_parser::CompilerRulesConcrete>());
    // -------------------------------------------------------------------------
    if (onerut_verbose) {
        const auto ast_asset_ast_chart = _ast_asset_head->to_ast_chart(onerut_parser::asset_to_esc_data);
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

#endif