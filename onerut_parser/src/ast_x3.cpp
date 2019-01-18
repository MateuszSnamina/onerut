#include<onerut_parser/ast_x3.hpp>

namespace onerut_parser::onerut_ast::x3 {

    struct to_string_visitor {
        typedef std::string result_type;
        template<typename T>
        result_type operator()(const T & i) const;
    };

    template<typename T>
    to_string_visitor::result_type to_string_visitor::operator()(const T & i) const {
        return to_string(i);
    }

    std::string to_string(const IdentifierInfo& i) {
        //boost::algorithm::join(other_chars, std::string(""))
        std::string result(1, i.first_char);
        for (unsigned idx = 0; idx < i.other_chars.size(); idx++) {
            result += std::string(1, i.other_chars[idx]);
        }
        // POPRAWIC IMPLEMENTACJE!!
        return result;
    }

    std::string to_string(const LitIntInfo& i) {
        return std::to_string(i.value);
    }

    std::string to_string(const LitDoubleInfo& i) {
        return std::to_string(i.value);
    }

    std::string to_string(const FunctionInfo& i) {
        std::string result;
        result += to_string(i.name);
        result += "[";
        for (const ExpressionInfo& temp : i.argv) {
            result += to_string(temp);
            result += ",";
        }
        result += "]";
        return result;
    }

    std::string to_string(const ExpressionInfo& i) {
        //return "55";
        return boost::apply_visitor(to_string_visitor(), i);
    }

}