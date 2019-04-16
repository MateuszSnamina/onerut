#ifndef ONERUT_PARSER_GRAMMA_PARSER
#define ONERUT_PARSER_GRAMMA_PARSER

#include<string>
#include<boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include<string_utils/string_span.hpp>
#include<onerut_parser_exec/ast_x3.hpp>

namespace onerut_parser {

    struct X3ParseResultInfo {
        std::shared_ptr<const std::string> input;
        std::string::const_iterator it;        
        const bool match;
        const onerut_parser::onerut_ast::x3::ExpressionInfo ast_head;
        const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >> positions;
        bool hit_end() const;
        bool succes() const;        
        string_const_span parsed_span() const;
        string_const_span not_parsed_span() const;
    };

    void print(X3ParseResultInfo info);

    X3ParseResultInfo parse(std::shared_ptr<const std::string> input);

}

#endif