#include<onerut_parser_exec/ast_source.hpp>

namespace onerut_parser::onerut_ast::source {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    LinesStyledChartInfo SourceNode::to_ast_chart() const {
        LinesStyledChartInfo ast_chart;
        to_ast_chart(0, ast_chart);
        return ast_chart;
    }

    void SourceNode::to_ast_chart_disregard_subsource(
            unsigned deepness,
            LinesStyledChartInfo& ast_chart) const {
        while (ast_chart.size() <= deepness)
            ast_chart.emplace_back();
        const esc::EscData esc_data = esc::EscDataBuilder() << esc::manip::build_esc_data;
        const LineBitStyledChartInfo bit = {span, esc_data};
        ast_chart[deepness].push_back(bit);
    }

    // -------------------------------------------------------------------------

    void WithNoSubsourcesNode::to_ast_chart(
            unsigned deepness,
            LinesStyledChartInfo& ast_chart) const {
        to_ast_chart_disregard_subsource(deepness, ast_chart);
    }

    void WithOneSubsourceNode::to_ast_chart(
            unsigned deepness,
            LinesStyledChartInfo& ast_chart) const {
        to_ast_chart_disregard_subsource(deepness, ast_chart);
        arg->to_ast_chart(deepness + 1, ast_chart);
    }

    void WithTwoSubsourcesNode::to_ast_chart(
            unsigned deepness,
            LinesStyledChartInfo& ast_chart) const {
        to_ast_chart_disregard_subsource(deepness, ast_chart);
        first_arg->to_ast_chart(deepness + 1, ast_chart);
        second_arg->to_ast_chart(deepness + 1, ast_chart);
    }

    void WithOneOrMoreSubsourcesNode::to_ast_chart(
            unsigned deepness,
            LinesStyledChartInfo& ast_chart) const {
        to_ast_chart_disregard_subsource(deepness, ast_chart);
        first_arg->to_ast_chart(deepness + 1, ast_chart);
        for (const auto& arg : other_argv) {
            arg->to_ast_chart(deepness + 1, ast_chart);
        }
    }

    void WithAnyNumberOfSubsourcesNode::to_ast_chart(
            unsigned deepness,
            LinesStyledChartInfo& ast_chart) const {
        to_ast_chart_disregard_subsource(deepness, ast_chart);
        for (const auto& arg : argv) {
            arg->to_ast_chart(deepness + 1, ast_chart);
        }
    }

}
