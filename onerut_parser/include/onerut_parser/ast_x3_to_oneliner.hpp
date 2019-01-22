#ifndef ONERUT_PARSER_AST_X3_TO_ONELINER
#define ONERUT_PARSER_AST_X3_TO_ONELINER

#include<onerut_parser/ast_x3.hpp>

namespace onerut_parser::onerut_ast::x3 {

    std::u32string to_oneliner(const ExpressionInfo& info);
    std::u32string to_oneliner(const OpPlusMinusInfo& info);
    std::u32string to_oneliner(const OpProdDivInfo& info);
    std::u32string to_oneliner(const OpPowInfo& info);
    std::u32string to_oneliner(const OpAtInfo& info);
    std::u32string to_oneliner(const OpArrowInfo& info);
    std::u32string to_oneliner(const OpGlueInfo& info);
    std::u32string to_oneliner(const Value1Info& info);
    std::u32string to_oneliner(const LitDoubleInfo& info);
    std::u32string to_oneliner(const LitIntInfo& info);    
    std::u32string to_oneliner(const OpUnaryPlusMinusInfo& info);
    std::u32string to_oneliner(const Value2Info& info);
    std::u32string to_oneliner(const FunctionInfo& info);
    std::u32string to_oneliner(const IdentifierInfo& info);
    std::u32string to_oneliner(const NestedExpression1Info& info);
    std::u32string to_oneliner(const NestedExpression2Info& info);

}

#endif