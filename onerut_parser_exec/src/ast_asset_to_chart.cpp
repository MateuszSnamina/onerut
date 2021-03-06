#include<onerut_parser_exec/ast_asset.hpp>

namespace onerut_parser_exec::onerut_ast::asset {

    // -------------------------------------------------------------------------

    LinesChartInfo AssetNode::to_ast_chart(
            std::function<esc::EscData(const Asset&)> asset_to_esc_data) const {
        LinesChartInfo ast_chart;
        to_ast_chart(0, ast_chart, asset_to_esc_data);
        return ast_chart;
    }

    void AssetNode::to_ast_chart(
            unsigned deepness,
            LinesChartInfo & ast_chart,
            std::function<esc::EscData(const Asset&)> asset_to_esc_data) const {
        while (ast_chart.size() <= deepness)
            ast_chart.emplace_back();
        const auto esc_data = asset_to_esc_data(asset);
        BitChartInfo bit = {source->span, esc_data};
        ast_chart[deepness].push_back(bit);
        for (const auto& subasset : subnodes) {
            subasset->to_ast_chart(deepness + 1, ast_chart, asset_to_esc_data);
        }
    }

    // -------------------------------------------------------------------------

    ErrorsChartInfo AssetNode::to_errors_chart() const {
        ErrorsChartInfo erros_chart;
        to_errors_chart(erros_chart);
        return erros_chart;
    }

    void AssetNode::to_errors_chart(
            ErrorsChartInfo& erros_chart) const {
        if (const auto& error = asset.deref().compile_error_or_empty()) {
            if (!std::dynamic_pointer_cast<CompileArgumentsError>(*error)) {
                const std::string message = (*error)->what();
                const string_utils::string_const_span span = source->span;
                const ErrorChartInfo error_info = {span, message};
                erros_chart.push_back(error_info);
            }
        }
        for (const auto& subasset : subnodes) {
            subasset->to_errors_chart(erros_chart);
        }
    }

    // -------------------------------------------------------------------------

}
