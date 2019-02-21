#include<onerut_parser/ast_asset.hpp>
#include<onerut_parser/asset_to_esc_data.hpp>


namespace onerut_parser::onerut_ast::asset {

    LinesStyledChartInfo AssetNode::to_ast_chart() const {
        LinesStyledChartInfo ast_chart;
        to_ast_chart(0, ast_chart);
        return ast_chart;
    }

    void AssetNode::to_ast_chart(
            unsigned deepness,
            LinesStyledChartInfo & ast_chart) const {
        while (ast_chart.size() <= deepness)
            ast_chart.emplace_back();
        esc::EscData esc_data = asset_to_esc_data(asset);
        LineBitStyledChartInfo bit = {source->span, esc_data};
        ast_chart[deepness].push_back(bit);
        for (const auto& subsource : subsources) {
            subsource->to_ast_chart(deepness + 1, ast_chart);
        }
    }

    ErrorsChartInfo AssetNode::to_errors_chart() const {

    }

    void AssetNode::to_errors_chart(
            ErrorsChartInfo& erros_chart) const {

    }

}
