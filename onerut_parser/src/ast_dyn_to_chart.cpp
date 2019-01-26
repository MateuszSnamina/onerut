#include<onerut_parser/ast_dyn.hpp>

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
        esc::EscData esc_data = get_print_style();
        LineBitStyledChartInfo bit = {span, esc_data};
        chart[deepness].push_back(bit);
    }

    esc::EscData ExpressionNode::get_print_style() const {
        return esc::EscDataBuilder() << esc::manip::build_esc_data;
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

    esc::EscData IdentifierNode::get_print_style() const {
        return esc::EscDataBuilder() << esc::manip::blue << esc::manip::build_esc_data;
    } // bedzie do usuniecia!!


}
