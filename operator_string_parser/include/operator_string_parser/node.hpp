#ifndef OPERATR_STRING_PARSER_NODE_HPP
#define OPERATR_STRING_PARSER_NODE_HPP

#include<operator_string_parser/span.hpp>
#include<memory>
#include<vector>

namespace operator_string_parser {

    class Node {
    public:
        Node(string_const_span span);

        enum class Type {
            unrevealed,
            const_int,
            const_double,
            expression,
            one_electon_operator,
            many_electon_operator
        };
        const string_const_span span;
        virtual std::string str() const = 0;
        Type type;
        virtual ~Node() = default;
    };

    class ConstIntNode : public Node {
    public:
        ConstIntNode(string_const_span span, int value);
        virtual std::string str() const override;
        const int value;
    };

    class ConstDoubleNode : public Node {
    public:
        ConstDoubleNode(string_const_span span, double value);
        virtual std::string str() const override;
        const double value;
    };

    class FunctionNode : public Node {
    public:
        FunctionNode(string_const_span span, std::string name, std::vector<std::shared_ptr<Node>> argv);
        virtual std::string str() const override;
        const std::string name;
        const std::vector<std::shared_ptr<Node>> argv;
    };

    class ExpressionNode : public Node {
    public:
        ExpressionNode(string_const_span span, std::string expr_string);
        virtual std::string str() const override;
        const std::string expr_string;
        // TO DO exprtk        
    };

    class InvalidNode : public Node {
    public:
        InvalidNode(string_const_span span);
        virtual std::string str() const override;
    };

    std::shared_ptr<Node> span_to_node(string_const_span span);
}


#endif