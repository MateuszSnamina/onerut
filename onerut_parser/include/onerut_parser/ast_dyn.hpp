#ifndef ONERUT_PARSER_AST_DYN
#define ONERUT_PARSER_AST_DYN

#include<string>
#include<vector>
#include<memory>

#include<onerut_parser/string_span.hpp>
#include<onerut_parser/compile_result.hpp>
#include<onerut_parser/print_chart.hpp>

namespace onerut_parser::onerut_ast::compile_result {
    class CompileResultNode;
}

namespace onerut_parser::onerut_ast::dyn {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    class ExpressionNode : public std::enable_shared_from_this<ExpressionNode> {
    public:
        ExpressionNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span);
        const std::shared_ptr<const std::u32string> input;
        const u32string_const_span span;
        virtual ~ExpressionNode() = 0;
        virtual std::u32string to_oneliner() const = 0;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const = 0;
        LinesStyledChartInfo to_chart() const;
        virtual void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const = 0;
        virtual void to_chart_disregard_subexpression(
                unsigned deepness,
                LinesStyledChartInfo& chart) const;
    };

    // -------------------------------------------------------------------------

    class WithNoSubexpressionsNode : public ExpressionNode {
    public:
        WithNoSubexpressionsNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile() const = 0;
    };

    class WithOneSubexpressionNode : public ExpressionNode {
    public:
        WithOneSubexpressionNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                const std::shared_ptr<ExpressionNode> arg);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile(CompileResult arg_compile_result) const = 0;
        const std::shared_ptr<ExpressionNode> arg;
    };

    class WithTwoSubexpressionsNode : public ExpressionNode {
    public:
        WithTwoSubexpressionsNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const = 0;
        const std::shared_ptr<ExpressionNode> first_arg;
        const std::shared_ptr<ExpressionNode> second_arg;
    };

    class WithOneOrMoreSubexpressionsNode : public ExpressionNode {
    public:
        WithOneOrMoreSubexpressionsNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::vector<std::shared_ptr<ExpressionNode>> other_argv);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const = 0;
        const std::shared_ptr<ExpressionNode> first_arg;
        const std::vector<std::shared_ptr<ExpressionNode>> other_argv;
    };

    class WithAnyNumberOfSubexpressionsNode : public ExpressionNode {
    public:
        WithAnyNumberOfSubexpressionsNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::vector<std::shared_ptr<ExpressionNode>> argv);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile(std::vector<CompileResult> argv_compile_result) const = 0;
        const std::vector<std::shared_ptr<ExpressionNode>> argv;
    };

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    class IdentifierNode : public WithNoSubexpressionsNode {
    public:
        IdentifierNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::u32string name);
        std::u32string to_oneliner() const override;
        CompileResult basic_compile() const override;
        const std::u32string name;
    };

    class LitLongNode : public WithNoSubexpressionsNode {
    public:
        LitLongNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                long value);
        std::u32string to_oneliner() const override;
        CompileResult basic_compile() const override;
        const long value;
    };

    class LitDoubleNode : public WithNoSubexpressionsNode {
    public:
        LitDoubleNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                double value);
        std::u32string to_oneliner() const override;
        CompileResult basic_compile() const override;
        const double value;
    };

    class OpAssignNode : public WithTwoSubexpressionsNode {
    public:
        OpAssignNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg,
                bool new_flag,
                bool const_flag);
        std::u32string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
        const bool new_flag;
        const bool const_flag;
    };

    class OpPlusMinusNode : public WithOneOrMoreSubexpressionsNode {
    public:
        OpPlusMinusNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::vector<std::shared_ptr<ExpressionNode>> other_argv,
                std::vector<char32_t> opv);
        std::u32string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const override;
        const std::vector<char32_t> opv;
    };

    class OpProdDivNode : public WithOneOrMoreSubexpressionsNode {
    public:
        OpProdDivNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::vector<std::shared_ptr<ExpressionNode>> other_argv,
                std::vector<char32_t> opv);
        std::u32string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const override;
        const std::vector<char32_t> opv;
    };

    class OpPowNode : public WithTwoSubexpressionsNode {
    public:
        OpPowNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        std::u32string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
    };

    class OpAtNode : public WithTwoSubexpressionsNode {
    public:
        OpAtNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        std::u32string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
    };

    class OpArrowNode : public WithTwoSubexpressionsNode {
    public:
        OpArrowNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        std::u32string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
    };

    class OpGlueNode : public WithTwoSubexpressionsNode {
    public:
        OpGlueNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        std::u32string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
    };

    class UnaryPlusMinusNode : public WithOneSubexpressionNode {
    public:
        UnaryPlusMinusNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                char32_t op,
                std::shared_ptr<ExpressionNode> expression);
        std::u32string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult arg_compile_result) const override;
        const char32_t op;
    };

    class FunctionNode : public WithAnyNumberOfSubexpressionsNode {
    public:
        FunctionNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::u32string name,
                std::vector<std::shared_ptr<ExpressionNode>> argv);
        std::u32string to_oneliner() const override;
        virtual CompileResult basic_compile(std::vector<CompileResult> argv_compile_result) const override;
        const std::u32string name;
    };

}

#endif
