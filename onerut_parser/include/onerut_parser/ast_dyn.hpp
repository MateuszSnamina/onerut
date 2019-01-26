#ifndef ONERUT_PARSER_DYN_X3
#define ONERUT_PARSER_DYN_X3

#include<string>
#include<vector>
#include<memory>

#include<onerut_parser/string_span.hpp>
#include<onerut_parser/print_chart.hpp>

namespace onerut_parser::onerut_ast::dyn {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    class ExpressionNode {
    public:
        ExpressionNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span);
        const std::shared_ptr<const std::u32string> input;
        const u32string_const_span span;
        virtual ~ExpressionNode() = 0;
        virtual std::u32string to_oneliner() const = 0;
        LinesStyledChartInfo to_chart() const;
        virtual void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const = 0;
        virtual void to_chart_disregard_subexpression(
                unsigned deepness,
                LinesStyledChartInfo& chart) const;
        virtual esc::EscData get_print_style() const;
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
    };

    class WithOneSubexpressionNode : public ExpressionNode {
    public:
        WithOneSubexpressionNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                const std::shared_ptr<ExpressionNode> expression);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        const std::shared_ptr<ExpressionNode> expression;
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
        esc::EscData get_print_style() const override; // bedzie do usuniecia!!
        const std::u32string name;
    };

    class LitIntNode : public WithNoSubexpressionsNode {
    public:
        LitIntNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                int value);
        std::u32string to_oneliner() const override;
        const int value;
    };

    class LitDoubleNode : public WithNoSubexpressionsNode {
    public:
        LitDoubleNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                double value);
        std::u32string to_oneliner() const override;
        const double value;
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
    };

    class OpAtNode : public WithTwoSubexpressionsNode {
    public:
        OpAtNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        std::u32string to_oneliner() const override;
    };

    class OpArrowNode : public WithTwoSubexpressionsNode {
    public:
        OpArrowNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        std::u32string to_oneliner() const override;
    };

    class OpGlueNode : public WithTwoSubexpressionsNode {
    public:
        OpGlueNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        std::u32string to_oneliner() const override;
    };

    class UnaryPlusMinusNode : public WithOneSubexpressionNode {
    public:
        UnaryPlusMinusNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                char32_t op,
                std::shared_ptr<ExpressionNode> expression);
        std::u32string to_oneliner() const override;
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
        const std::u32string name;
    };

}

#endif