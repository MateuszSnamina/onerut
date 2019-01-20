#ifndef ONERUT_PARSER_AST_X3_TO_STRING
#define ONERUT_PARSER_AST_X3_TO_STRING

#include<onerut_parser/ast_x3.hpp>

namespace onerut_parser::onerut_ast::x3 {

    std::u32string to_u32string(const IdentifierInfo& info);
    std::u32string to_u32string(const LitIntInfo& info);
    std::u32string to_u32string(const LitDoubleInfo& info);
    std::u32string to_u32string(const NestedExpressionInfo& info);
    std::u32string to_u32string(const OpPlusInfo& info);
    std::u32string to_u32string(const OpProdInfo& info);    
    std::u32string to_u32string(const FunctionInfo& info);
    std::u32string to_u32string(const ExpressionInfo& info);

}

#endif