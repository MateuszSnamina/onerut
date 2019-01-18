#include<iostream>

#include<boost/range.hpp>
#include<vector>
#include<boost/variant.hpp>

//#include<boost/algorithm/string/join.hpp>

#include<boost/fusion/adapted/struct.hpp>//??
#include<boost/spirit/home/x3.hpp>
#include<boost/spirit/home/x3/support/ast/variant.hpp>
#include<onerut/ast_x3.hpp>


// This to be in global scope:
#include<boost/fusion/adapted/struct.hpp>

//BOOST_FUSION_ADAPT_STRUCT(ast::IdentifierInfo, (char, first_char))
BOOST_FUSION_ADAPT_STRUCT(ast::IdentifierInfo, (char, first_char)(std::vector<char>, other_chars))
BOOST_FUSION_ADAPT_STRUCT(ast::LitIntInfo, (int, value))
BOOST_FUSION_ADAPT_STRUCT(ast::LitDoubleInfo, (double, value))
BOOST_FUSION_ADAPT_STRUCT(ast::FunctionInfo, (ast::IdentifierInfo, name)(std::vector<ast::ExpressionInfo>, argv))


// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//struct position_cache_tag;
struct position_cache_tag {
};

struct annotate_position {

    template <typename T, typename Iterator, typename Context>
    inline void on_success(Iterator const& first, Iterator const& last
            , T& ast, Context const& context) {
        auto& position_cache = boost::spirit::x3::get<position_cache_tag>(context).get();
        position_cache.annotate(ast, first, last);
    }
};

//namespace x3 = boost::spirit::x3;


namespace one_rut_parser {

    struct IndentifierParser : annotate_position {
    };

    struct LitIntParser : annotate_position {
    };

    struct LitDoubleParser : annotate_position {
    };

    struct FunctionParser : annotate_position {
    };

    struct ExpressionParser {
    };

    boost::spirit::x3::rule<class IndentifierParser, ast::IdentifierInfo > const indentifier_parser = "indentifier_parser";
    boost::spirit::x3::rule<class LitIntParser, ast::LitIntInfo > const lit_int_parser = "lit_int_parser";
    boost::spirit::x3::rule<class LitDoubleParser, ast::LitDoubleInfo > const lit_double_parser = "lit_double_parser";
    boost::spirit::x3::rule<class FunctionParser, ast::FunctionInfo > const function_parser = "function_parser";
    boost::spirit::x3::rule<class ExpressionParser, ast::ExpressionInfo > const expression_parser = "expression_parser"; //, qi::space_type
    auto const indentifier_parser_def = boost::spirit::x3::lexeme[boost::spirit::x3::char_("A-Za-z_") >> *boost::spirit::x3::char_("A-Za-z1-9_")];
    auto const lit_int_parser_def = boost::spirit::x3::int_;
    auto const lit_double_parser_def = boost::spirit::x3::double_;
    auto const function_parser_def = indentifier_parser >> '(' >> expression_parser % ',' >> ')';
    auto const expression_parser_def = lit_int_parser | lit_double_parser | function_parser | indentifier_parser;
    //auto const expression_parser_def = lit_int_parser | lit_double_parser | indentifier_parser;
    //auto const expression_parser_def = lit_int_parser | lit_double_parser;
    BOOST_SPIRIT_DEFINE(indentifier_parser, lit_int_parser, lit_double_parser, function_parser, expression_parser)
    //BOOST_SPIRIT_DEFINE(indentifier_parser, lit_int_parser, lit_double_parser, expression_parser)
    //BOOST_SPIRIT_DEFINE(indentifier_parser)
}

void onerut_parse(const std::string& s) {
    ast::ExpressionInfo head;
    //ast::FunctionInfo head;
    //ast::IdentifierInfo head;
    using boost::spirit::x3::ascii::space;
    boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >> positions
    {
        s.begin(), s.end()
    };

    auto const parser = boost::spirit::x3::with<position_cache_tag>(std::ref(positions))[one_rut_parser::expression_parser];
    //auto const parser = boost::spirit::x3::with<position_cache_tag>(std::ref(positions))[one_rut_parser::function_parser];
    //auto const parser = boost::spirit::x3::with<position_cache_tag>(std::ref(positions))[one_rut_parser::indentifier_parser];
    bool r = phrase_parse(s.begin(), s.end(), parser, space, head);
    //    std::cout << r << std::endl;

    //std::cout << boost::apply_visitor(ast::expression_printer(), head) << std::endl;
    //std::cout << positions.position_of(head).begin() - s.begin() << std::endl;
    //std::cout << positions.position_of(head).end() - s.begin() << std::endl;
    //std::cout << std::string(positions.position_of(head).begin(), positions.position_of(head).end()) << std::endl;

}
