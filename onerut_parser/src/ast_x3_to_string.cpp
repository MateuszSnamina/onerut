#include<onerut_parser/ast_x3.hpp>
#include<onerut_parser/unicode_support.hpp>

namespace onerut_parser::onerut_ast::x3 {

    // -------------------------------------------------------------------------
    // ------------- VISITOR ---------------------------------------------------
    // -------------------------------------------------------------------------

    struct to_string_visitor {
        typedef std::u32string result_type;
        template<typename T>
        result_type operator()(const T & i) const;
    };

    template<typename T>
    to_string_visitor::result_type to_string_visitor::operator()(const T & i) const {
        return to_u32string(i);
    }

    // -------------------------------------------------------------------------
    // ------------- FUNCTIONS FOR EXPRESSION ----------------------------------
    // -------------------------------------------------------------------------

    std::u32string to_u32string(const ExpressionInfo& info) {
        return boost::apply_visitor(to_string_visitor(), info);
    }

    // -------------------------------------------------------------------------
    // ------------- FUNCTIONS FOR CONCRETE EXPRESSION TYPES -------------------
    // -------------------------------------------------------------------------

    std::u32string to_u32string(const IdentifierInfo& info) {
        return info.name();
    }

    std::u32string to_u32string(const LitIntInfo& info) {
        return unicode_from_utf8(std::to_string(info.value));
    }

    std::u32string to_u32string(const LitDoubleInfo& info) {
        return unicode_from_utf8(std::to_string(info.value));
    }

    std::u32string to_u32string(const NestedExpressionInfo& info) {
        std::u32string result;
        result += U"[";
            result += to_u32string(info.expression);
        result += U"]";
        return result;        
    }

    std::u32string to_u32string(const OpPlusInfo& info) {
        std::u32string result;
        result += U"[";
        for (const ExpressionInfo& arg_info : info.argv) {
            result += to_u32string(arg_info);
            result += U"+";
        }
        result += U"]";
        return result;        
    }

    std::u32string to_u32string(const OpProdInfo& info) {
        std::u32string result;
        result += U"[";
        for (const ExpressionInfo& arg_info : info.argv) {
            result += to_u32string(arg_info);
            result += U"*";
        }
        result += U"]";
        return result;        
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

}