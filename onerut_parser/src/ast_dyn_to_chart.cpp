#include<onerut_parser/ast_dyn.hpp>

namespace onerut_parser::onerut_ast::dyn {

    std::vector<std::u32string> ExpressionNode::to_chart() const {
        std::vector<std::u32string> chart;
        to_chart(0, chart);
        return chart;
    }

    void ExpressionNode::to_chart(
            unsigned deepness,
            std::vector<std::u32string>& chart) const {
        while (chart.size() <= deepness)
            chart.emplace_back(input->begin() - input->end(), U'░');
        const unsigned offset = span.begin() - input->cbegin();
        std::copy(span.begin(), span.end(), chart[deepness].begin() + offset);
    }

    void WithNoSubexpressionsNode::to_chart(
            unsigned deepness,
            std::vector<std::u32string>& chart) const {
        ExpressionNode::to_chart(deepness, chart);
        // Do nothing more!
    }

    void WithOneSubexpressionNode::to_chart(
            unsigned deepness,
            std::vector<std::u32string>& chart) const {
        ExpressionNode::to_chart(deepness, chart);
        expression->to_chart(deepness + 1, chart);
    }

    void WithTwoSubexpressionsNode::to_chart(
            unsigned deepness,
            std::vector<std::u32string>& chart) const {
        ExpressionNode::to_chart(deepness, chart);
        first_arg->to_chart(deepness + 1, chart);
        second_arg->to_chart(deepness + 1, chart);
    }

    void WithOneOrMoreSubexpressionsNode::to_chart(
            unsigned deepness,
            std::vector<std::u32string>& chart) const {
        ExpressionNode::to_chart(deepness, chart);
        first_arg->to_chart(deepness + 1, chart);
        for (const auto& arg : other_argv) {
            arg->to_chart(deepness + 1, chart);
        }
    }

    void WithAnyNumberOfSubexpressionsNode::to_chart(
            unsigned deepness,
            std::vector<std::u32string>& chart) const {
        ExpressionNode::to_chart(deepness, chart);
        for (const auto& arg : argv) {
            arg->to_chart(deepness + 1, chart);
        }
    }

}
