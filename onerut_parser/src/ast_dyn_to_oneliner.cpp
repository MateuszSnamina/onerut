#include<onerut_parser/ast_dyn.hpp>

//#include<cassert>
//#include<algorithm>

namespace onerut_parser::onerut_ast::dyn {
/*
    ExpressionNode::ExpressionNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span) :
    input(input),
    span(span) {
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        assert(span.begin() < span.end());
    }

    ExpressionNode::~ExpressionNode() {
    }


    IdentifierNode::IdentifierNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::u32string name) :
    ExpressionNode(input, span),
    name(name) {
    }

    OpPlusMinusNode::OpPlusMinusNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::vector<std::shared_ptr<ExpressionNode>> other_argv,
            std::vector<char32_t> opv) :
    ExpressionNode(input, span),
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        const auto predicate = [](char32_t op) {
            return op == L'+' || op == L'-';
        };
        assert(std::all_of(opv.cbegin(), opv.cend(), predicate));
    }

    OpProdDivNode::OpProdDivNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::vector<std::shared_ptr<ExpressionNode>> other_argv,
            std::vector<char32_t> opv) :
    ExpressionNode(input, span),
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        const auto predicate = [](char32_t op) {
            return op == L'*' || op == L'/';
        };
        assert(std::all_of(opv.cbegin(), opv.cend(), predicate));
    }

    OpPowNode::OpPowNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::shared_ptr<ExpressionNode> second_arg) :
    ExpressionNode(input, span),
    first_arg(first_arg),
    second_arg(second_arg) {
    }

    OpAtNode::OpAtNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::shared_ptr<ExpressionNode> second_arg) :
    ExpressionNode(input, span),
    first_arg(first_arg),
    second_arg(second_arg) {
    }

    OpArrowNode::OpArrowNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::shared_ptr<ExpressionNode> second_arg) :
    ExpressionNode(input, span),
    first_arg(first_arg),
    second_arg(second_arg) {
    }

    OpGlueNode::OpGlueNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::shared_ptr<ExpressionNode> second_arg) :
    ExpressionNode(input, span),
    first_arg(first_arg),
    second_arg(second_arg) {
    }

    UnaryPlusMinusNode::UnaryPlusMinusNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            char32_t op,
            std::shared_ptr<ExpressionNode> expression) :
    ExpressionNode(input, span),
    op(op),
    expression(expression) {
        assert(op == L'+' || op == L'-');
    }

    LitIntNode::LitIntNode(std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            int value) :
    ExpressionNode(input, span),
    value(value) {
    }

    LitDoubleNode::LitDoubleNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            double value) :
    ExpressionNode(input, span),
    value(value) {
    }

    FunctionNode::FunctionNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::u32string name,
            std::vector<std::shared_ptr<ExpressionNode>> argv) :
    ExpressionNode(input, span),
    name(name),
    argv(argv) {
    }
*/
}
