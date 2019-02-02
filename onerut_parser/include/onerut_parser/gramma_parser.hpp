#ifndef ONERUT_PARSER_GRAMMA_PARSER
#define ONERUT_PARSER_GRAMMA_PARSER

#include<string>
#include<boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include<onerut_parser/ast_x3.hpp>

namespace onerut_parser {

    struct X3ParseResultInfo {
        std::shared_ptr<const std::u32string> input;
        const bool match;
        const bool hit_end;
        bool succes() const;
        const onerut_parser::onerut_ast::x3::ExpressionInfo ast_head;
        const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >> positions;
    };

    void print(X3ParseResultInfo info);

    X3ParseResultInfo parse(std::shared_ptr<const std::u32string> input);
    //X3ParseResultInfo parse(const std::u32string input);
    //X3ParseResultInfo parse(const std::string input);

}

#endif