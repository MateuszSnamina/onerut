#include<operator_string_parser/node.hpp>
#include<operator_string_parser/parse_XXX_string.hpp>
#include<memory>

namespace {

    std::shared_ptr<operator_string_parser::Node> _span_to_node(
            operator_string_parser::string_const_span span,
            const std::string function_name,
            const std::vector<operator_string_parser::string_const_span> arg_sub_spans) {
        std::vector<std::shared_ptr < operator_string_parser::Node>> function_args_nodes;
        function_args_nodes.reserve(arg_sub_spans.size());
        for (const auto & arg_sub_span : arg_sub_spans) {
            const auto arg_node = operator_string_parser::span_to_node(arg_sub_span);
            function_args_nodes.push_back(arg_node);
        }
        return std::make_shared<operator_string_parser::FunctionNode>(span, function_name, function_args_nodes);
    }
}

namespace operator_string_parser {

    Node::Node(string_const_span span) :
    span(span) {
    }

    ConstIntNode::ConstIntNode(
            string_const_span span,
            int value) :
    Node(span),
    value(value) {
    }

    std::string ConstIntNode::str() const {
        return "⟦" + std::to_string(value) + "⟧";
    }

    ConstDoubleNode::ConstDoubleNode(
            string_const_span span,
            double value) :
    Node(span),
    value(value) {
    }

    std::string ConstDoubleNode::str() const {
        return "⟦" + std::to_string(value) + "⟧";
    }
    //〘〙

    FunctionNode::FunctionNode(
            string_const_span span,
            std::string name, std::vector<std::shared_ptr<Node>> argv) :
    Node(span),
    name(name),
    argv(argv) {
    }

    std::string FunctionNode::str() const {
        std::string result;
        result = "⟦" + name + "⇨";
        for (const auto & arg : argv) {
            result += arg->str();
        }
        result += "⟧";
        return result;
    }

    ExpressionNode::ExpressionNode(
            string_const_span span,
            std::string expr_string) :
    Node(span),
    expr_string(expr_string) {
    }

    std::string ExpressionNode::str() const {
        return "⟦E⇨" + expr_string + "⟧";
    }

    InvalidNode::InvalidNode(
            string_const_span span) :
    Node(span) {
    }

    std::string InvalidNode::str() const {
        return "⟦I⇨" + string_span_to_string(span) + "⟧";
    }

    // *************************************************************************

    std::shared_ptr<Node> span_to_node(
            string_const_span span) {

        span = lrstrip(span);
        while (is_outer_nested(span)) {
            span = _disregard_one_outer_nesting(span);
            span = lrstrip(span);
        }

        if (const auto value = try_parse_int(span)) {
            return std::make_shared<ConstIntNode>(span, *value);
        }

        if (const auto value = try_parse_double(span)) {
            return std::make_shared<ConstDoubleNode>(span, *value);
        }

        if (auto expression_string = try_parse_expression(span)) {
            return std::make_shared<ExpressionNode>(span, *expression_string);
        }

        if (const auto ingredient_sub_spans = try_parse_infix_operator(span, '+')) {
            return _span_to_node(span, "plus", *ingredient_sub_spans);
        }

        if (const auto factors_sub_spans = try_parse_infix_operator(span, '*')) {
            return _span_to_node(span, "prod", *factors_sub_spans);
        }

        if (const auto function_info = try_parse_function(span)) {
            const std::string function_name = string_span_to_string((*function_info).name);
            const std::vector<string_const_span> arg_sub_spans = (*function_info).argv;
            return _span_to_node(span, function_name, arg_sub_spans);
        }

        return std::make_shared<InvalidNode>(span);
    }

}