#include<onerut_parser_exec/ast_source.hpp>

#include<cassert>
#include<algorithm>

namespace onerut_parser_exec::onerut_ast::source {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************    

    SourceNode::SourceNode(
            std::shared_ptr<const std::string> input,
            string_const_span span) :
    input(input),
    span(span) {
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        assert(span.begin() < span.end());
    }

    SourceNode::~SourceNode() {
    }

    WithNoSubsourcesNode::WithNoSubsourcesNode(
            std::shared_ptr<const std::string> input,
            string_const_span span) :
    SourceNode(input, span) {
    }

    WithOneSubsourceNode::WithOneSubsourceNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            const std::shared_ptr<SourceNode> arg) :
    SourceNode(input, span),
    arg(arg) {
    }

    WithTwoSubsourcesNode::WithTwoSubsourcesNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::shared_ptr<SourceNode> first_arg,
            std::shared_ptr<SourceNode> second_arg) :
    SourceNode(input, span),
    first_arg(first_arg),
    second_arg(second_arg) {
    }

    WithOneOrMoreSubsourcesNode::WithOneOrMoreSubsourcesNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::shared_ptr<SourceNode> first_arg,
            std::vector<std::shared_ptr<SourceNode>> other_argv) :
    SourceNode(input, span),
    first_arg(first_arg),
    other_argv(other_argv) {
    }

    WithAnyNumberOfSubsourcesNode::WithAnyNumberOfSubsourcesNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::vector<std::shared_ptr<SourceNode>> argv) :
    SourceNode(input, span),
    argv(argv) {
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    IdentifierNode::IdentifierNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::string name) :
    WithNoSubsourcesNode(input, span),
    name(name) {
    }

    OpAssignNode::OpAssignNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::shared_ptr<SourceNode> first_arg,
            std::shared_ptr<SourceNode> second_arg,
            bool new_flag,
            bool const_flag) :
    WithTwoSubsourcesNode(input, span, first_arg, second_arg),
    new_flag(new_flag),
    const_flag(const_flag) {
    }

    OpPlusMinusNode::OpPlusMinusNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::shared_ptr<SourceNode> first_arg,
            std::vector<std::shared_ptr<SourceNode>> other_argv,
            std::vector<char> opv) :
    WithOneOrMoreSubsourcesNode(input, span, first_arg, other_argv),
    opv(opv) {
        const auto predicate = [](char op) {
            return op == L'+' || op == L'-';
        };
        assert(std::all_of(opv.cbegin(), opv.cend(), predicate));
    }

    OpProdDivNode::OpProdDivNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::shared_ptr<SourceNode> first_arg,
            std::vector<std::shared_ptr<SourceNode>> other_argv,
            std::vector<char> opv) :
    WithOneOrMoreSubsourcesNode(input, span, first_arg, other_argv),
    opv(opv) {
        const auto predicate = [](char op) {
            return op == L'*' || op == L'/';
        };
        assert(std::all_of(opv.cbegin(), opv.cend(), predicate));
    }

    OpPowNode::OpPowNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::shared_ptr<SourceNode> first_arg,
            std::shared_ptr<SourceNode> second_arg) :
    WithTwoSubsourcesNode(input, span, first_arg, second_arg) {
    }

    OpAtNode::OpAtNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::shared_ptr<SourceNode> first_arg,
            std::shared_ptr<SourceNode> second_arg) :
    WithTwoSubsourcesNode(input, span, first_arg, second_arg) {
    }

    OpArrowNode::OpArrowNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::shared_ptr<SourceNode> first_arg,
            std::shared_ptr<SourceNode> second_arg) :
    WithTwoSubsourcesNode(input, span, first_arg, second_arg) {
    }

    OpGlueNode::OpGlueNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::shared_ptr<SourceNode> first_arg,
            std::shared_ptr<SourceNode> second_arg) :
    WithTwoSubsourcesNode(input, span, first_arg, second_arg) {
    }

    UnaryPlusMinusNode::UnaryPlusMinusNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            char op,
            std::shared_ptr<SourceNode> arg) :
    WithOneSubsourceNode(input, span, arg),
    op(op) {
        assert(op == L'+' || op == L'-');
    }

    LitLongNode::LitLongNode(std::shared_ptr<const std::string> input,
            string_const_span span,
            long value) :
    WithNoSubsourcesNode(input, span),
    value(value) {
    }

    LitDoubleNode::LitDoubleNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            double value) :
    WithNoSubsourcesNode(input, span),
    value(value) {
    }

    LitPureComplexDoubleNode::LitPureComplexDoubleNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            double value) :
    WithNoSubsourcesNode(input, span),
    value(value) {
    }

    FunctionNode::FunctionNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::string name,
            std::vector<std::shared_ptr<SourceNode>> argv) :
    WithAnyNumberOfSubsourcesNode(input, span, argv),
    name(name) {
    }

}
