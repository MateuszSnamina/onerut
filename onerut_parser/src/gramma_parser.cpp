#include<iostream>
//#include<boost/algorithm/string/join.hpp>
#include<boost/fusion/adapted/struct.hpp>
#include<boost/spirit/home/x3.hpp>

#include<onerut_parser/ast_x3.hpp>

// -----------------------------------------------------------------------------
// This to be in global scope:
#include<boost/fusion/adapted/struct.hpp>
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::IdentifierInfo,
        (char, first_char)
        (std::vector<char>, other_chars))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::LitIntInfo,
        (int, value))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::LitDoubleInfo,
        (double, value))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::FunctionInfo,
        (onerut_parser::onerut_ast::x3::IdentifierInfo, name)
        (std::vector<onerut_parser::onerut_ast::x3::ExpressionInfo>, argv))

// -----------------------------------------------------------------------------
namespace {

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
}

// -----------------------------------------------------------------------------
namespace onerut_parser::onerut_gramma {

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

    boost::spirit::x3::rule<class IndentifierParser, onerut_ast::x3::IdentifierInfo > const indentifier_parser = "indentifier_parser";
    boost::spirit::x3::rule<class LitIntParser, onerut_ast::x3::LitIntInfo > const lit_int_parser = "lit_int_parser";
    boost::spirit::x3::rule<class LitDoubleParser, onerut_ast::x3::LitDoubleInfo > const lit_double_parser = "lit_double_parser";
    boost::spirit::x3::rule<class FunctionParser, onerut_ast::x3::FunctionInfo > const function_parser = "function_parser";
    boost::spirit::x3::rule<class ExpressionParser, onerut_ast::x3::ExpressionInfo > const expression_parser = "expression_parser"; //, qi::space_type
    auto const indentifier_parser_def = boost::spirit::x3::lexeme[boost::spirit::x3::char_("A-Za-z_") >> *boost::spirit::x3::char_("A-Za-z1-9_")];

    auto const lit_int_parser_def = boost::spirit::x3::int_;
    auto const lit_double_parser_def = boost::spirit::x3::double_;
    auto const function_parser_def = indentifier_parser >> '(' >> expression_parser % ',' >> ')';
    auto const expression_parser_def = lit_int_parser | lit_double_parser | function_parser | indentifier_parser;

    BOOST_SPIRIT_DEFINE(indentifier_parser, lit_int_parser, lit_double_parser, function_parser, expression_parser)

}

// -----------------------------------------------------------------------------
namespace onerut_parser {

    bool parse(const std::string& s) {
        onerut_parser::onerut_ast::x3::ExpressionInfo ast_head;
        using boost::spirit::x3::ascii::space;
        boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >> positions
        {
            s.begin(), s.end()
        };

        auto const parser = boost::spirit::x3::with<position_cache_tag>(std::ref(positions))[onerut_parser::onerut_gramma::expression_parser];
        std::string::const_iterator it = s.begin();
        const bool match = phrase_parse(it, s.end(), parser, space, ast_head);
        const bool hit_end = (it == s.end());
        std::cout << match << " " << hit_end << std::endl;

        std::cout << to_string(ast_head) << std::endl;
        std::cout << positions.position_of(ast_head).begin() - s.begin() << std::endl;
        std::cout << positions.position_of(ast_head).end() - s.begin() << std::endl;
        std::cout << std::string(positions.position_of(ast_head).begin(), positions.position_of(ast_head).end()) << std::endl;
        return match && hit_end;
    }

}