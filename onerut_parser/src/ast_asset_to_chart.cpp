#include<onerut_parser/ast_asset.hpp>
#include<onerut_parser/asset_to_esc_data.hpp>

namespace onerut_parser::onerut_ast::asset {

    LinesStyledChartInfo AssetNode::to_chart() const {
        LinesStyledChartInfo chart;
        to_chart(0, chart);
        return chart;
    }

    void AssetNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo & chart) const {
        while (chart.size() <= deepness)
            chart.emplace_back();
        esc::EscData esc_data = asset_to_esc_data(asset);
        LineBitStyledChartInfo bit = {source->span, esc_data};
        chart[deepness].push_back(bit);
        for (const auto& subsource : subsources) {
            subsource->to_chart(deepness + 1, chart);
        }
    }

}
