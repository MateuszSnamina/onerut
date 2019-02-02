#include<onerut_parser/ast_source.hpp>

#include<cassert>
#include<algorithm>

namespace onerut_parser::onerut_ast::source {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************    

    ExpressionNode::ExpressionNode (
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

    WithNoSubexpressionsNode::WithNoSubexpressionsNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span) :
    ExpressionNode(input, span) {
    }

    WithOneSubexpressionNode::WithOneSubexpressionNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            const std::shared_ptr<ExpressionNode> arg) :
    ExpressionNode(input, span),
    arg(arg) {
    }

    WithTwoSubexpressionsNode::WithTwoSubexpressionsNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::shared_ptr<ExpressionNode> second_arg) :
    ExpressionNode(input, span),
    first_arg(first_arg),
    second_arg(second_arg) {
    }

    WithOneOrMoreSubexpressionsNode::WithOneOrMoreSubexpressionsNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::vector<std::shared_ptr<ExpressionNode>> other_argv) :
    ExpressionNode(input, span),
    first_arg(first_arg),
    other_argv(other_argv) {
    }

    WithAnyNumberOfSubexpressionsNode::WithAnyNumberOfSubexpressionsNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::vector<std::shared_ptr<ExpressionNode>> argv) :
    ExpressionNode(input, span),
    argv(argv) {
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    IdentifierNode::IdentifierNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::u32string name) :
    WithNoSubexpressionsNode(input, span),
    name(name) {
    }

    OpAssignNode::OpAssignNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::shared_ptr<ExpressionNode> second_arg,
            bool new_flag,
            bool const_flag) :
    WithTwoSubexpressionsNode(input, span, first_arg, second_arg),
    new_flag(new_flag),
    const_flag(const_flag) {
    }

    OpPlusMinusNode::OpPlusMinusNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::vector<std::shared_ptr<ExpressionNode>> other_argv,
            std::vector<char32_t> opv) :
    WithOneOrMoreSubexpressionsNode(input, span, first_arg, other_argv),
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
    WithOneOrMoreSubexpressionsNode(input, span, first_arg, other_argv),
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
    WithTwoSubexpressionsNode(input, span, first_arg, second_arg) {
    }

    OpAtNode::OpAtNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::shared_ptr<ExpressionNode> second_arg) :
    WithTwoSubexpressionsNode(input, span, first_arg, second_arg) {
    }

    OpArrowNode::OpArrowNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::shared_ptr<ExpressionNode> second_arg) :
    WithTwoSubexpressionsNode(input, span, first_arg, second_arg) {
    }

    OpGlueNode::OpGlueNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::shared_ptr<ExpressionNode> first_arg,
            std::shared_ptr<ExpressionNode> second_arg) :
    WithTwoSubexpressionsNode(input, span, first_arg, second_arg) {
    }

    UnaryPlusMinusNode::UnaryPlusMinusNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            char32_t op,
            std::shared_ptr<ExpressionNode> expression) :
    WithOneSubexpressionNode(input, span, expression),
    op(op) {
        assert(op == L'+' || op == L'-');
    }

    LitLongNode::LitLongNode(std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            long value) :
    WithNoSubexpressionsNode(input, span),
    value(value) {
    }

    LitDoubleNode::LitDoubleNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            double value) :
    WithNoSubexpressionsNode(input, span),
    value(value) {
    }

    FunctionNode::FunctionNode(
            std::shared_ptr<const std::u32string> input,
            u32string_const_span span,
            std::u32string name,
            std::vector<std::shared_ptr<ExpressionNode>> argv) :
    WithAnyNumberOfSubexpressionsNode(input, span, argv),
    name(name) {
    }

}
