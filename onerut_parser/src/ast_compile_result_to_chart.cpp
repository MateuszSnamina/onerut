#include<onerut_parser/ast_compile_result.hpp>
#include<onerut_parser/compile_result_to_esc_data.hpp>

namespace onerut_parser::onerut_ast::compile_result {

    LinesStyledChartInfo CompileResultNode::to_chart() const {
        LinesStyledChartInfo chart;
        to_chart(0, chart);
        return chart;
    }

    void CompileResultNode::to_chart(
            unsigned deepness,
            LinesStyledChartInfo & chart) const {
        while (chart.size() <= deepness)
            chart.emplace_back();
        esc::EscData esc_data = compile_result_to_esc_data(compile_result);
        LineBitStyledChartInfo bit = {expression->span, esc_data};
        chart[deepness].push_back(bit);
        for (const auto& subexpression : subexpressions) {
            subexpression->to_chart(deepness + 1, chart);
        }
    }

}
