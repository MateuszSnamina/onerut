#ifndef ONERUT_PARSER_AST_X3_TO_STRING
#define ONERUT_PARSER_AST_X3_TO_STRING

#include<onerut_parser/ast_x3.hpp>

namespace onerut_parser::onerut_ast::x3 {

    std::u32string to_u32string(const ExpressionInfo& info);
    //std::u32string to_u32string(const OpPlusInfo& info);
    std::u32string to_u32string(const OpPlusMinusInfo& info);
    std::u32string to_u32string(const OpProdDivInfo& info);
    std::u32string to_u32string(const OpPowInfo& info);
    std::u32string to_u32string(const OpAtInfo& info);
    std::u32string to_u32string(const OpArrowInfo& info);
    std::u32string to_u32string(const OpGlueInfo& info);
    std::u32string to_u32string(const ValueInfo& info);
    std::u32string to_u32string(const LitDoubleInfo& info);
    std::u32string to_u32string(const LitIntInfo& info);
    std::u32string to_u32string(const FunctionInfo& info);
    std::u32string to_u32string(const IdentifierInfo& info);
    std::u32string to_u32string(const NestedExpressionInfo& info);

}

#endif