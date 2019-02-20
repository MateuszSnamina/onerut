#include<onerut_parser/ast_source.hpp>
#include<onerut_parser/asset_to_esc_data.hpp>

namespace onerut_parser::onerut_ast::source {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    LinesStyledChartInfo SourceNode::to_chart() const {
        LinesStyledChartInfo chart;
        to_chart(0, chart);
        return chart;
    }

    void SourceNode::to_chart_disregard_subsource(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        while (chart.size() <= deepness)
            chart.emplace_back();
        const esc::EscData esc_data = esc::EscDataBuilder() << esc::manip::build_esc_data;
        const LineBitStyledChartInfo bit = {span, esc_data};
        chart[deepness].push_back(bit);
    }

    // -------------------------------------------------------------------------

    void WithNoSubsourcesNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subsource(deepness, chart);
    }

    void WithOneSubsourceNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subsource(deepness, chart);
        arg->to_chart(deepness + 1, chart);
    }

    void WithTwoSubsourcesNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subsource(deepness, chart);
        first_arg->to_chart(deepness + 1, chart);
        second_arg->to_chart(deepness + 1, chart);
    }

    void WithOneOrMoreSubsourcesNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subsource(deepness, chart);
        first_arg->to_chart(deepness + 1, chart);
        for (const auto& arg : other_argv) {
            arg->to_chart(deepness + 1, chart);
        }
    }

    void WithAnyNumberOfSubsourcesNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subsource(deepness, chart);
        for (const auto& arg : argv) {
            arg->to_chart(deepness + 1, chart);
        }
    }

}
