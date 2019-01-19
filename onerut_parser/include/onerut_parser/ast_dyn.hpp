#ifndef ONERUT_PARSER_DYN_X3
#define ONERUT_PARSER_DYN_X3

namespace onerut_parser::onerut_ast::dyn {

    class AbstractAstNode {
    public:
        ~AbstractAstNode() = 0;
    }

    AbstractAstNode::~AbstractAstNode() {
    }

    class IdentifierNode : public AbstractAstNode {
    };

    class LitIntNode : public AbstractAstNode {
    };

    class LitDoubleNode : public AbstractAstNode {
    };

    class FunctionInfo : public AbstractAstNode {
    };
}

#endif