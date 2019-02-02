#ifndef ONERUT_PARSER_AST_COMPILE_RESULT
#define ONERUT_PARSER_AST_COMPILE_RESULT

#include<string>
#include<vector>
#include<memory>

#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/ast_dyn.hpp>

namespace onerut_parser::onerut_ast::dyn {
    class ExpressionNode;
} // ZROBIC FORWARD???? TODO

namespace onerut_parser::onerut_ast::compile_result {

    class CompileResultNode {
    public:
        CompileResultNode(
                std::shared_ptr<const dyn::ExpressionNode> expression,
                CompileResult compile_result
                );
        CompileResultNode(
                std::shared_ptr<const dyn::ExpressionNode> expression,
                std::shared_ptr<CompileResultNode> subexpression,
                CompileResult compile_result);
        CompileResultNode(
                std::shared_ptr<const dyn::ExpressionNode> expression,
                std::shared_ptr<CompileResultNode> first_subexpression,
                std::shared_ptr<CompileResultNode> second_subexpression,
                CompileResult compile_result);
        CompileResultNode(
                std::shared_ptr<const dyn::ExpressionNode> expression,
                std::shared_ptr<CompileResultNode> first_subexpression,
                std::vector<std::shared_ptr<CompileResultNode>> others_subexpressions,
                CompileResult compile_result);
        CompileResultNode(
                std::shared_ptr<const dyn::ExpressionNode> expression,
                std::vector<std::shared_ptr<CompileResultNode>> subexpressions,
                CompileResult compile_result);
        virtual ~CompileResultNode() = default;
        // To-chart functions:
        LinesStyledChartInfo to_chart() const;
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const;
        // Internal data:
        const std::shared_ptr<const dyn::ExpressionNode> expression;
        const std::vector<std::shared_ptr<CompileResultNode>> subexpressions;
        const CompileResult compile_result;
    };

}

#endif
