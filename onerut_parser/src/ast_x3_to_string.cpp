#include<onerut_parser/unicode_support.hpp>
#include<onerut_parser/ast_x3.hpp>
#include<onerut_parser/ast_x3_to_string.hpp>

namespace onerut_parser::onerut_ast::x3 {

    // -------------------------------------------------------------------------
    // ------------- VISITOR ---------------------------------------------------
    // -------------------------------------------------------------------------

    struct to_string_visitor {
        typedef std::u32string result_type;
        template<typename T>
        result_type operator()(const T & info) const;
    };

    template<typename T>
    to_string_visitor::result_type to_string_visitor::operator()(const T & info) const {
        return to_u32string(info);
    }

    // -------------------------------------------------------------------------
    // -------------- FUNCTIONS FOR CONCRETE AST TYPES -------------------------
    // -------------------------------------------------------------------------

    std::u32string to_u32string(const ExpressionInfo& info) {
        return to_u32string(info.sum);
    }

    std::u32string to_u32string(const OpPlusMinusInfo& info) {
        std::u32string result;
        result += U"[";
        result += to_u32string(info.first_arg);
        for (const OpPlusMinusBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == U'+' || arg_info.op == U'-');
            result += arg_info.op;
            result += to_u32string(arg_info.arg);
        }
        result += U"]";
        return result;
    }

    std::u32string to_u32string(const OpProdDivInfo& info) {
        std::u32string result;
        result += U"[";
        result += to_u32string(info.first_arg);
        for (const OpProdDivBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == U'*' || arg_info.op == U'/');
            result += arg_info.op;
            result += to_u32string(arg_info.arg);
        }
        result += U"]";
        return result;
    }

    std::u32string to_u32string(const OpPowInfo& info) {
        std::u32string result;
        result += to_u32string(info.first_arg);
        if (info.other_arg) {
            result += U"^";
            result += to_u32string(*info.other_arg);
        }
        return result;
    }

    std::u32string to_u32string(const OpAtInfo& info) {
        std::u32string result;
        result += to_u32string(info.first_arg);
        if (info.other_arg) {
            result += U"@";
            result += to_u32string(*info.other_arg);
        }
        return result;
    }

    std::u32string to_u32string(const OpArrowInfo& info) {
        std::u32string result;
        result += to_u32string(info.first_arg);
        if (info.other_arg) {
            result += U"->";
            result += to_u32string(*info.other_arg);
        }
        return result;
    }

    std::u32string to_u32string(const OpGlueInfo& info) {
        std::u32string result;
        result += to_u32string(info.first_arg);
        if (info.other_arg) {
            result += U"::";
            result += to_u32string(*info.other_arg);
        }
        return result;
    }

    std::u32string to_u32string(const UnaryPlusMinusInfo& info) {
        std::u32string result;
        if (info.op) {
            assert(info.op == U'+' || info.op == U'-');
            result += *info.op;
        }        
        result += U"+[";
        result += to_u32string(info.expression);
        result += U"]";
        return result;
    }

    std::u32string to_u32string(const ValueInfo& info) {
        return boost::apply_visitor(to_string_visitor(), info);
    }

    std::u32string to_u32string(const LitDoubleInfo& info) {
        return unicode_from_utf8(std::to_string(info.value));
    }

    std::u32string to_u32string(const LitIntInfo& info) {
        return unicode_from_utf8(std::to_string(info.value));
    }

    std::u32string to_u32string(const FunctionInfo& info) {
        std::u32string result;
        result += to_u32string(info.name);
        result += U"[";
        for (const ExpressionInfo& arg_info : info.argv) {
            result += to_u32string(arg_info);
            result += U",";
        }
        result += U"]";
        return result;
    }

    std::u32string to_u32string(const IdentifierInfo& info) {
        return info.name();
    }

    std::u32string to_u32string(const NestedExpression1Info& info) {
        std::u32string result;
        result += U"[";
        result += to_u32string(info.expression);
        result += U"]";
        return result;
    }

    std::u32string to_u32string(const NestedExpression2Info& info) {
        std::u32string result;
        result += U"[";
        result += to_u32string(info.expression);
        result += U"]";
        return result;
    }

}