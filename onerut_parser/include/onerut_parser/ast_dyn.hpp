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
                std::shared_ptr<const std::string> input,
                string_const_span span);
        const std::shared_ptr<const std::string> input;
        const string_const_span span;
        virtual ~ExpressionNode() = 0;
    };

    class IdentifierNode : public ExpressionNode {
        IdentifierNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::string name);
        const std::string name;
    };

    class LitIntNode : public ExpressionNode {
        LitIntNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                int value);
        const int value;
    };

    class LitDoubleNode : public ExpressionNode {
        LitDoubleNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                double value);
        const double value;
    };

    class FunctionNode : public ExpressionNode {
        FunctionNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::string name,
                std::vector<std::shared_ptr<ExpressionNode>> argv);
        const std::string name;
        std::vector<std::shared_ptr<ExpressionNode>> argv;
    };

}

#endif