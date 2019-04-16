#ifndef ONERUT_PARSER_AST_X3_TO_ONELINER
#define ONERUT_PARSER_AST_X3_TO_ONELINER

#include<onerut_parser_exec/ast_x3.hpp>

namespace onerut_parser_exec::onerut_ast::x3 {

    std::string to_oneliner(const ExpressionInfo& info);
    std::string to_oneliner(const OpAssignInfo& info);
    std::string to_oneliner(const OpPlusMinusInfo& info);
    std::string to_oneliner(const OpProdDivInfo& info);
    std::string to_oneliner(const OpPowInfo& info);
    std::string to_oneliner(const OpAtInfo& info);
    std::string to_oneliner(const OpArrowInfo& info);
    std::string to_oneliner(const OpGlueInfo& info);
    std::string to_oneliner(const Value1Info& info);
    std::string to_oneliner(const LitDoubleInfo& info);
    std::string to_oneliner(const LitPureComplexDoubleInfo& info);
    std::string to_oneliner(const LitLongInfo& info);
    std::string to_oneliner(const OpUnaryPlusMinusInfo& info);
    std::string to_oneliner(const Value2Info& info);
    std::string to_oneliner(const FunctionInfo& info);
    std::string to_oneliner(const EmptyFunctionInfo& info);    
    std::string to_oneliner(const IdentifierInfo& info);
    std::string to_oneliner(const NestedExpression1Info& info);
    std::string to_oneliner(const NestedExpression2Info& info);

}

#endif