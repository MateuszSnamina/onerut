#include<iterator>

#include<string_utils/greek_support.hpp>

#include<onerut_request/request_imperative.hpp>
#include<onerut_request/request_print_value.hpp>
#include<onerut_parser_exec/gramma_parser.hpp>
#include<onerut_parser_exec/ast_x3_to_ast_source.hpp>
#include<onerut_parser_exec/ast_asset.hpp>
#include<onerut_parser_exec/print_chart.hpp>
#include<onerut_parser_rules/asset_receipt.hpp>
#include<onerut_parser_rules/compiler_rules_concrete.hpp>
#include<onerut_parser_rules/asset_to_esc_data.hpp>

#include<onerut/line_processor.hpp>

std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>
process_line(std::shared_ptr<const std::string> line) {
    // *************************************************************************
    std::cout << esc::manip::bg_yellow << "Processsing "
            << esc::manip::blue << string_utils::StreamToGreek(*line) << esc::manip::color_default
            << "...";
    std::cout << std::endl;
    // *************************************************************************
    // *************  The Parser stage    **************************************
    // *************************************************************************    
    const auto parsed_x3_info = onerut_parser_exec::parse(line);
    // -------------------------------------------------------------------------
    //    print(parsed_x3_info);
    if (!parsed_x3_info.succes()) {
        if (!parsed_x3_info.match) {
            std::cout << "Fail to parse line: " << std::endl;
            std::cout << esc::manip::red << string_utils::StreamToGreek(*line) << esc::manip::reset << "." << std::endl;
        } else {
            const auto parsed_view = string_utils::to_string_view(parsed_x3_info.parsed_span());
            const auto not_parsed_view = string_utils::to_string_view(parsed_x3_info.not_parsed_span());
            std::cout << esc::manip::bg_green << string_utils::StreamToGreek(parsed_view)
                    << esc::manip::bg_red << string_utils::StreamToGreek(not_parsed_view);
            std::cout << std::endl;
        }
        return nullptr;
    }
    // *************************************************************************
    // *************  The source creation stage:     ***************************
    // *************************************************************************    
    const auto ast_source_head = onerut_parser_exec::onerut_ast::to_ast_source(
            parsed_x3_info.ast_head,
            parsed_x3_info.input,
            parsed_x3_info.positions);
    // -------------------------------------------------------------------------
    // const auto ast_source_ast_chart = ast_source_head->to_ast_chart();
    // onerut_parser::print_ast_chart(parsed_x3_info.input, ast_source_ast_chart, , "[source ] ");
    // *************************************************************************
    // *************  Compilation stage:     ***********************************
    // *************************************************************************
    const auto ast_asset_head = ast_source_head->compile(std::make_shared<onerut_parser_rules::CompilerRulesConcrete>());
    // -------------------------------------------------------------------------
    const auto asset_ast_chart = ast_asset_head->to_ast_chart(onerut_parser_rules::asset_to_esc_data);
    onerut_parser_exec::print_ast_chart(std::cout, parsed_x3_info.input, asset_ast_chart, "[diagram] ");
    const auto asset_errors_chart = ast_asset_head->to_errors_chart();
    onerut_parser_exec::print_errors_chart(std::cout, parsed_x3_info.input, asset_errors_chart, "[errors ] ");
    const auto& asset = ast_asset_head->asset;
    onerut_parser_rules::print_receipt(std::cout, asset, "[receipt] ");
    // *************************************************************************
    return ast_asset_head;
}

std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>
process_imperative_line(std::shared_ptr<const std::string> line) {
    // *************************************************************************
    const auto ast_asset_head = process_line(line);
    // *************************************************************************
    // *************  Requests stage:        ***********************************
    // *************************************************************************
    if (ast_asset_head) {
        const auto& asset = ast_asset_head->asset;
        if (const auto request = asset.deref().typed_value_or_empty<onerut_request::ImperativeRequest>()) {
            std::cout << "[request] [process] Onerut is about to execute the imperative request."
                    << std::endl;
            (*request)->exec();
            std::cout << "[request] [process] Onerut has executed the imperative request."
                    << std::endl;
        }
        if (const auto request = asset.deref().typed_value_or_empty<onerut_request::PrintValueRequest>()) {
            (*request)->print(std::cout, "[request] ");
        }
    }
    // *************************************************************************
    std::cout << std::endl;
    return ast_asset_head;
}

std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>
process_declarative_line(std::shared_ptr<const std::string> line) {
    // *************************************************************************
    const auto ast_asset_head = process_line(line);
    // *************************************************************************
    // *************  Requests stage:        ***********************************
    // *************************************************************************
    if (ast_asset_head) {
        const auto& asset = ast_asset_head->asset;
        if (const auto request = asset.deref().typed_value_or_empty<onerut_request::ImperativeRequest>()) {
            std::cout << "[request] [warning] Imperative requests has no effect in the declarative mode."
                    << std::endl;
        }
        if (const auto request = asset.deref().typed_value_or_empty<onerut_request::PrintValueRequest>()) {
            std::cout << "[request] [info] The value will be printed in every self-consistent loop iteration as well as in the final summary."
                    << std::endl;            
        }
    }
    // *************************************************************************
    std::cout << std::endl;
    return ast_asset_head;
}

std::vector<std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>>
process_imperative_lines(const std::vector<std::shared_ptr<const std::string>>&lines) {
    std::vector<std::shared_ptr < onerut_parser_exec::onerut_ast::asset::AssetNode>> result;
    std::transform(cbegin(lines), cend(lines), std::back_inserter(result),
            [](const std::shared_ptr<const std::string> &line) {
                return process_imperative_line(line);
            });
    return result;
}

std::vector<std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>>
process_declarative_lines(const std::vector<std::shared_ptr<const std::string>>&lines) {
    std::vector<std::shared_ptr < onerut_parser_exec::onerut_ast::asset::AssetNode>> result;
    std::transform(cbegin(lines), cend(lines), std::back_inserter(result),
            [](const std::shared_ptr<const std::string> &line) {
                return process_declarative_line(line);
            });
    return result;
}