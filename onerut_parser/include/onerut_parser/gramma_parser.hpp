#ifndef ONERUT_GRAMMA_PARSER
#define ONERUT_GRAMMA_PARSER

#include<string>
#include<boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include<onerut_parser/ast_x3.hpp>

namespace onerut_parser {
    
    struct ParseResultInfo {
        const bool match;
        const bool hit_end;
        const bool succes;
        const onerut_parser::onerut_ast::x3::ExpressionInfo ast_head;
        const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >> positions;        
    };
    
    ParseResultInfo parse(const std::u32string& input);
    ParseResultInfo parse(const std::string input);    
}

#endif