#ifndef ONERUT_PARSER_DYN_X3
#define ONERUT_PARSER_DYN_X3

#include<string>
#include<vector>
#include<memory>

#include<onerut_parser/string_span.hpp>

namespace onerut_parser::onerut_ast::dyn {

    class ExpressionNode {
    public:
        ExpressionNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span);
        const std::shared_ptr<const std::u32string> input;
        const u32string_const_span span;
        virtual ~ExpressionNode() = 0;
    };

    class IdentifierNode : public ExpressionNode {
    public:
        IdentifierNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::u32string name);
        const std::u32string name;
    };

    class LitIntNode : public ExpressionNode {
    public:
        LitIntNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                int value);
        const int value;
    };

    class LitDoubleNode : public ExpressionNode {
    public:
        LitDoubleNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                double value);
        const double value;
    };

    class OpPlusMinusNode : public ExpressionNode {
    public:
        OpPlusMinusNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::vector<std::shared_ptr<ExpressionNode>> other_argv,
                std::vector<char32_t> opv);
        const std::shared_ptr<ExpressionNode> first_arg;
        const std::vector<std::shared_ptr<ExpressionNode>> other_argv;
        const std::vector<char32_t> opv;
    };

    class OpProdDivNode : public ExpressionNode {
    public:
        OpProdDivNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::vector<std::shared_ptr<ExpressionNode>> other_argv,
                std::vector<char32_t> opv);
        const std::shared_ptr<ExpressionNode> first_arg;
        const std::vector<std::shared_ptr<ExpressionNode>> other_argv;
        const std::vector<char32_t> opv;
    };

    class OpPowNode : public ExpressionNode {
    public:
        OpPowNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        const std::shared_ptr<ExpressionNode> first_arg;
        const std::shared_ptr<ExpressionNode> second_arg;
    };

    class OpAtNode : public ExpressionNode {
    public:
        OpAtNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        const std::shared_ptr<ExpressionNode> first_arg;
        const std::shared_ptr<ExpressionNode> second_arg;
    };

    class OpArrowNode : public ExpressionNode {
    public:
        OpArrowNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        const std::shared_ptr<ExpressionNode> first_arg;
        const std::shared_ptr<ExpressionNode> second_arg;
    };

    class OpGlueNode : public ExpressionNode {
    public:
        OpGlueNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::shared_ptr<ExpressionNode> first_arg,
                std::shared_ptr<ExpressionNode> second_arg);
        const std::shared_ptr<ExpressionNode> first_arg;
        const std::shared_ptr<ExpressionNode> second_arg;
    };

    class UnaryPlusMinusNode : public ExpressionNode {
    public:
        UnaryPlusMinusNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                char32_t op,
                std::shared_ptr<ExpressionNode> expression);
        const char32_t op;
        const std::shared_ptr<ExpressionNode> expression;
    };

    class FunctionNode : public ExpressionNode {
    public:
        FunctionNode(
                std::shared_ptr<const std::u32string> input,
                u32string_const_span span,
                std::u32string name,
                std::vector<std::shared_ptr<ExpressionNode>> argv);
        const std::u32string name;
        const std::vector<std::shared_ptr<ExpressionNode>> argv;
    };

}

#endif