#include<onerut/ast_x3.hpp>

namespace ast {
/*
    std::string IdentifierInfo::str() const {
        //boost::algorithm::join(other_chars, std::string(""))
        std::string result(1, first_char);
        for (unsigned idx = 0; idx < other_chars.size(); idx++) {
            result += std::string(1, other_chars[idx]);
        }
        // POPRAWIC IMPLEMENTACJE!!
        return result;
    }

    std::string LitIntInfo::str() const {
        return std::to_string(value);
    }

    std::string LitDoubleInfo::str() const {
        return std::to_string(value);
    }

    expression_printer::result_type expression_printer::operator()(const IdentifierInfo & i) const {
        //std::cout << "ID" << std::endl;
        return "[ID:" + i.str() + "]";
    }

    expression_printer::result_type expression_printer::operator()(const LitIntInfo & i) const {
        //std::cout << "Int" << std::endl;
        return "[I:" + i.str() + "]";
    }

    expression_printer::result_type expression_printer::operator()(const LitDoubleInfo & i) const {
        //std::cout << "Dou" << std::endl;
        return "[D:" + i.str() + "]";
    }

    expression_printer::result_type expression_printer::operator()(const FunctionInfo & i) const {
        //std::cout << "Fun" << std::endl;
        std::string result;
        result += i.name.str();
        result += "[";
        for (const ExpressionInfo& temp : i.argv) {
            result += to_string(temp);
            result += ",";
        }
        result += "]";
        return result;
    }

    std::string to_string(const ExpressionInfo& i) {
        return boost::apply_visitor(expression_printer(), i);
    }
*/
}