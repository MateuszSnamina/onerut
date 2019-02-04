#include<onerut_parser/ast_x3.hpp>

namespace onerut_parser::onerut_ast::x3 {

    std::string IdentifierInfo::name() const {
        std::string result(1, first_char);
        result.reserve(1 + other_chars.size());
        for (unsigned idx = 0; idx < other_chars.size(); idx++) {
            result += std::string(1, other_chars[idx]);
        }
        return result;
        // POPRAWIC IMPLEMENTACJE!!        
    }
    
}