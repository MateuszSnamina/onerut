#include<onerut_parser/unicode_support.hpp>
#include<onerut_parser/ast_x3.hpp>
#include<onerut_parser/ast_x3_to_oneliner.hpp>

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
        return to_oneliner(info);
    }

    // -------------------------------------------------------------------------
    // -------------- FUNCTIONS FOR CONCRETE AST TYPES -------------------------
    // -------------------------------------------------------------------------

    std::u32string to_oneliner(const ExpressionInfo& info) {
        return to_oneliner(info.sum);
    }

    std::u32string to_oneliner(const OpPlusMinusInfo& info) {
        std::u32string result;
        result += U"[";
        result += to_oneliner(info.first_arg);
        for (const OpPlusMinusBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == U'+' || arg_info.op == U'-');
            result += arg_info.op;
            result += to_oneliner(arg_info.arg);
        }
        result += U"]";
        return result;
    }

    std::u32string to_oneliner(const OpProdDivInfo& info) {
        std::u32string result;
        result += U"[";
        result += to_oneliner(info.first_arg);
        for (const OpProdDivBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == U'*' || arg_info.op == U'/');
            result += arg_info.op;
            result += to_oneliner(arg_info.arg);
        }
        result += U"]";
        return result;
    }

    std::u32string to_oneliner(const OpPowInfo& info) {
        std::u32string result;
        result += to_oneliner(info.first_arg);
        if (info.other_arg) {
            result += U"^";
            result += to_oneliner(*info.other_arg);
        }
        return result;
    }

    std::u32string to_oneliner(const OpAtInfo& info) {
        std::u32string result;
        result += to_oneliner(info.first_arg);
        if (info.other_arg) {
            result += U"@";
            result += to_oneliner(*info.other_arg);
        }
        return result;
    }

    std::u32string to_oneliner(const OpArrowInfo& info) {
        std::u32string result;
        result += to_oneliner(info.first_arg);
        if (info.other_arg) {
            result += U"->";
            result += to_oneliner(*info.other_arg);
        }
        return result;
    }

    std::u32string to_oneliner(const OpGlueInfo& info) {
        std::u32string result;
        result += to_oneliner(info.first_arg);
        if (info.other_arg) {
            result += U"::";
            result += to_oneliner(*info.other_arg);
        }
        return result;
    }

    std::u32string to_oneliner(const Value1Info& info) {
        return boost::apply_visitor(to_string_visitor(), info);
    }

    std::u32string to_oneliner(const LitDoubleInfo& info) {
        return unicode_from_utf8(std::to_string(info.value));
    }

    std::u32string to_oneliner(const LitIntInfo& info) {
        return unicode_from_utf8(std::to_string(info.value));
    }

    std::u32string to_oneliner(const OpUnaryPlusMinusInfo& info) {
        std::u32string result;
        if (info.op) {
            assert(info.op == U'+' || info.op == U'-');
            result += *info.op;
        }
        result += U"+[";
        result += to_oneliner(info.expression);
        result += U"]";
        return result;
    }

    std::u32string to_oneliner(const Value2Info& info) {
        return boost::apply_visitor(to_string_visitor(), info);
    }

    std::u32string to_oneliner(const FunctionInfo& info) {
        std::u32string result;
        result += to_oneliner(info.name);
        result += U"[";
        for (const ExpressionInfo& arg_info : info.argv) {
            result += to_oneliner(arg_info);
            result += U",";
        }
        result += U"]";
        return result;
    }

    std::u32string to_oneliner(const IdentifierInfo& info) {
        return info.name();
    }

    std::u32string to_oneliner(const NestedExpression1Info& info) {
        std::u32string result;
        result += U"[";
        result += to_oneliner(info.expression);
        result += U"]";
        return result;
    }

    std::u32string to_oneliner(const NestedExpression2Info& info) {
        std::u32string result;
        result += U"[";
        result += to_oneliner(info.expression);
        result += U"]";
        return result;
    }

}