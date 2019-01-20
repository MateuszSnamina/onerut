#include<onerut_parser/ast_dyn.hpp>

#include<cassert>

namespace onerut_parser::onerut_ast::dyn {

    ExpressionNode::ExpressionNode(std::shared_ptr<const std::string> input, string_const_span span) :
    input(input),
    span(span) {
        assert(input->begin() <= span.begin());
        assert(span.end() <= input->end());
        assert(span.begin() < span.end());
    }

    ExpressionNode::~ExpressionNode() {
    }

    IdentifierNode::IdentifierNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::string name) :
    ExpressionNode(input, span),
    name(name) {
    }

    LitIntNode::LitIntNode(std::shared_ptr<const std::string> input,
            string_const_span span,
            int value) :
    ExpressionNode(input, span),
    value(value) {
    }

    LitDoubleNode::LitDoubleNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            double value) :
    ExpressionNode(input, span),
    value(value) {
    }

    FunctionNode::FunctionNode(
            std::shared_ptr<const std::string> input,
            string_const_span span,
            std::string name,
            std::vector<std::shared_ptr<ExpressionNode>> argv) :
    ExpressionNode(input, span),
    name(name),
    argv(argv) {
    }

}
