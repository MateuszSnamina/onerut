#include<onerut_parser_exec/ast_x3.hpp>
#include<onerut_parser_exec/ast_x3_to_oneliner.hpp>

namespace {

    // -------------------------------------------------------------------------
    // ------------- VISITOR ---------------------------------------------------
    // -------------------------------------------------------------------------

    struct to_string_visitor {
        typedef std::string result_type;
        template<typename T>
        result_type operator()(const T & info) const;
    };

    template<typename T>
    to_string_visitor::result_type to_string_visitor::operator()(const T & info) const {
        return to_oneliner(info);
    }

}

namespace onerut_parser::onerut_ast::x3 {

    // -------------------------------------------------------------------------
    // -------------- FUNCTIONS FOR CONCRETE AST TYPES -------------------------
    // -------------------------------------------------------------------------

    std::string to_oneliner(const ExpressionInfo& info) {
        return to_oneliner(info.assign);
    }

    std::string to_oneliner(const OpAssignInfo& info) {
        std::string result;
        if (info.bit) {
            if ((*info.bit).new_flag) result += "NEW ";
            if ((*info.bit).const_flag) result += "CONST ";
            result += to_oneliner((*info.bit).identifier);
        }
        result += to_oneliner(info.sum);
        return result;
    }

    std::string to_oneliner(const OpPlusMinusInfo& info) {
        std::string result;
        result += "[";
        result += to_oneliner(info.first_arg);
        for (const OpPlusMinusBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == '+' || arg_info.op == '-');
            result += arg_info.op;
            result += to_oneliner(arg_info.arg);
        }
        result += "]";
        return result;
    }

    std::string to_oneliner(const OpProdDivInfo& info) {
        std::string result;
        result += "[";
        result += to_oneliner(info.first_arg);
        for (const OpProdDivBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == '*' || arg_info.op == '/');
            result += arg_info.op;
            result += to_oneliner(arg_info.arg);
        }
        result += "]";
        return result;
    }

    std::string to_oneliner(const OpPowInfo& info) {
        std::string result;
        result += to_oneliner(info.first_arg);
        if (info.other_arg) {
            result += "^";
            result += to_oneliner(*info.other_arg);
        }
        return result;
    }

    std::string to_oneliner(const OpAtInfo& info) {
        std::string result;
        result += to_oneliner(info.first_arg);
        if (info.other_arg) {
            result += "@";
            result += to_oneliner(*info.other_arg);
        }
        return result;
    }

    std::string to_oneliner(const OpArrowInfo& info) {
        std::string result;
        result += to_oneliner(info.first_arg);
        if (info.other_arg) {
            result += "->";
            result += to_oneliner(*info.other_arg);
        }
        return result;
    }

    std::string to_oneliner(const OpGlueInfo& info) {
        std::string result;
        result += to_oneliner(info.first_arg);
        if (info.other_arg) {
            result += "::";
            result += to_oneliner(*info.other_arg);
        }
        return result;
    }

    std::string to_oneliner(const Value1Info& info) {
        return boost::apply_visitor(to_string_visitor(), info);
    }

    std::string to_oneliner(const LitDoubleInfo& info) {
        return std::to_string(info.value);
    }

    std::string to_oneliner(const LitPureComplexDoubleInfo& info) {
        return std::to_string(info.value) + "i";
    }

    std::string to_oneliner(const LitLongInfo& info) {
        return std::to_string(info.value);
    }

    std::string to_oneliner(const OpUnaryPlusMinusInfo& info) {
        std::string result;
        if (info.op) {
            assert(info.op == '+' || info.op == '-');
            result += *info.op;
        }
        result += "+[";
        result += to_oneliner(info.expression);
        result += "]";
        return result;
    }

    std::string to_oneliner(const Value2Info& info) {
        return boost::apply_visitor(to_string_visitor(), info);
    }

    std::string to_oneliner(const FunctionInfo& info) {
        std::string result;
        result += to_oneliner(info.name);
        result += "[";
        for (const ExpressionInfo& arg_info : info.argv) {
            result += to_oneliner(arg_info);
            result += ",";
        }
        result += "]";
        return result;
    }

    std::string to_oneliner(const EmptyFunctionInfo& info) {
        std::string result;
        result += to_oneliner(info.name);
        result += "[]";
        return result;
    }
    
    std::string to_oneliner(const IdentifierInfo& info) {
        return info.name();
    }

    std::string to_oneliner(const NestedExpression1Info& info) {
        std::string result;
        result += "[";
        result += to_oneliner(info.expression);
        result += "]";
        return result;
    }

    std::string to_oneliner(const NestedExpression2Info& info) {
        std::string result;
        result += "[";
        result += to_oneliner(info.expression);
        result += "]";
        return result;
    }

}