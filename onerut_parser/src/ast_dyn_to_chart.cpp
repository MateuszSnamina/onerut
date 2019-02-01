#include<onerut_parser/ast_dyn.hpp>
#include<onerut_parser/compile_result_to_esc_data.hpp>

namespace onerut_parser::onerut_ast::dyn {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    LinesStyledChartInfo ExpressionNode::to_chart() const {
        LinesStyledChartInfo chart;
        to_chart(0, chart);
        return chart;
    }

    void ExpressionNode::to_chart_disregard_subexpression(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        while (chart.size() <= deepness)
            chart.emplace_back();
        esc::EscData esc_data = esc::EscDataBuilder() << esc::manip::build_esc_data;
        LineBitStyledChartInfo bit = {span, esc_data};
        chart[deepness].push_back(bit);
    }

    // -------------------------------------------------------------------------

    void WithNoSubexpressionsNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subexpression(deepness, chart);
    }

    void WithOneSubexpressionNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subexpression(deepness, chart);
        expression->to_chart(deepness + 1, chart);
    }

    void WithTwoSubexpressionsNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subexpression(deepness, chart);
        first_arg->to_chart(deepness + 1, chart);
        second_arg->to_chart(deepness + 1, chart);
    }

    void WithOneOrMoreSubexpressionsNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subexpression(deepness, chart);
        first_arg->to_chart(deepness + 1, chart);
        for (const auto& arg : other_argv) {
            arg->to_chart(deepness + 1, chart);
        }
    }

    void WithAnyNumberOfSubexpressionsNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo& chart) const {
        to_chart_disregard_subexpression(deepness, chart);
        for (const auto& arg : argv) {
            arg->to_chart(deepness + 1, chart);
        }
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

}
