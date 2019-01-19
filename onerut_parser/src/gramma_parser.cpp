#include<iostream>
#include<boost/spirit/home/x3.hpp>
#include<boost/spirit/home/x3/support/ast/variant.hpp>
#include<boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include<boost/spirit/home/x3/support/utility/error_reporting.hpp>
//#include<boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include<boost/fusion/adapted/struct.hpp>

#include<onerut_parser/unicode_support.hpp>
#include<onerut_parser/ast_x3.hpp>
#include<onerut_parser/ast_x3_to_string.hpp>
#include<onerut_parser/ast_x3_to_chart.hpp>
#include<onerut_parser/gramma_parser.hpp>

// -----------------------------------------------------------------------------
// This has to be in the global scope:
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::IdentifierInfo,
        (char32_t, first_char)
        (std::vector<char32_t>, other_chars))
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
        inline void on_success(
                Iterator const& first, Iterator const& last,
                T& ast, Context const& context);
    };

    template <typename T, typename Iterator, typename Context>
    inline void annotate_position::on_success(
            Iterator const& first, Iterator const& last,
            T& ast, Context const& context) {
        auto& position_cache =
                boost::spirit::x3::get<position_cache_tag>(context).get();
        position_cache.annotate(ast, first, last);
    }

    struct error_handler {
        template <typename Iterator, typename Exception, typename Context>
        boost::spirit::x3::error_handler_result on_error(
                Iterator& first, Iterator const& last,
                Exception const& x, Context const& context);
    };

    template <typename Iterator, typename Exception, typename Context>
    boost::spirit::x3::error_handler_result error_handler::on_error(
            Iterator& first, Iterator const& last,
            Exception const& x, Context const& context) {
        auto& error_handler =
                boost::spirit::x3::get<boost::spirit::x3::error_handler_tag>(context).get();
        std::string message =
                "Error! Expecting: " + x.which() + " here:";
        error_handler(x.where(), message);
        return boost::spirit::x3::error_handler_result::fail;
    }

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

    struct ExpressionParserRaw {
    };

    struct ExpressionParser : annotate_position, error_handler {
    };

    boost::spirit::x3::rule<class IndentifierParser, onerut_ast::x3::IdentifierInfo > const indentifier_parser = "indentifier_parser";
    boost::spirit::x3::rule<class LitIntParser, onerut_ast::x3::LitIntInfo > const lit_int_parser = "lit_int_parser";
    boost::spirit::x3::rule<class LitDoubleParser, onerut_ast::x3::LitDoubleInfo > const lit_double_parser = "lit_double_parser";
    boost::spirit::x3::rule<class FunctionParser, onerut_ast::x3::FunctionInfo > const function_parser = "function_parser";
    boost::spirit::x3::rule<class ExpressionParserRaw, onerut_ast::x3::ExpressionInfo > const expression_parser_raw = "expression_parser_raw"; //, qi::space_type
    boost::spirit::x3::rule<class ExpressionParser, onerut_ast::x3::ExpressionInfo > const expression_parser = "expression_parser"; //, qi::space_type

    //auto const indentifier_parser_def = boost::spirit::x3::lexeme[boost::spirit::x3::char_("A-Za-z_") >> *boost::spirit::x3::char_("A-Za-z1-9_") >> !boost::spirit::x3::char_('(')];
    auto const indentifier_parser_def = boost::spirit::x3::lexeme[boost::spirit::x3::char_("A-Za-z_") >> *boost::spirit::x3::char_("A-Za-z1-9_")];
    auto const lit_int_parser_def = boost::spirit::x3::int_;
    auto const lit_double_parser_def = boost::spirit::x3::double_;
    auto const function_parser_def = indentifier_parser >> '(' >> expression_parser % ',' >> ')';
    auto const expression_parser_raw_def = lit_int_parser | lit_double_parser | function_parser | indentifier_parser;
    auto const expression_parser_def = boost::spirit::x3::expect[expression_parser_raw];

    BOOST_SPIRIT_DEFINE(indentifier_parser, lit_int_parser, lit_double_parser, function_parser, expression_parser, expression_parser_raw)
}

// -----------------------------------------------------------------------------

namespace onerut_parser {

    ParseResultInfo parse(const std::u32string& s) {
        // Iterators:
        const std::u32string::const_iterator input_begin = s.cbegin();
        const std::u32string::const_iterator input_end = s.cend();
        std::u32string::const_iterator it = input_begin;
        // Results:
        onerut_parser::onerut_ast::x3::ExpressionInfo ast_head;
        boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >> positions(input_begin, input_end);
        // Annotation, positions_handlers, error_handlers:
        boost::spirit::x3::error_handler<std::u32string::const_iterator> error_handler(it, input_end, std::cerr);
        // The Parser, parse:
        auto const parser =
                boost::spirit::x3::with<boost::spirit::x3::error_handler_tag>(std::ref(error_handler))[
                boost::spirit::x3::with<position_cache_tag>(std::ref(positions))[
                onerut_parser::onerut_gramma::expression_parser
                ]];
        const bool match = phrase_parse(it, s.end(), parser, boost::spirit::x3::ascii::space, ast_head);
        const bool hit_end = (it == s.end());
        // Print info:
        std::cout << "match:   " << match << std::endl;
        std::cout << "hit_end: " << hit_end << std::endl;
        if (match) {
            std::vector<std::u32string> chart = to_u32string_chart(ast_head, positions);
            const std::u32string table_horizontal_line(input_end - input_begin + 2, U'▓');
            std::cout << unicode_to_utf8(table_horizontal_line) << std::endl;
            std::cout << "▓" << unicode_to_utf8(s) << "▓" << std::endl;
            std::cout << unicode_to_utf8(table_horizontal_line) << std::endl;
            for (unsigned line = 0; line < chart.size(); line++) {
                std::cout << "▓" << unicode_to_utf8(chart[line]) << "▓" << std::endl;
            }
            std::cout << unicode_to_utf8(table_horizontal_line) << std::endl;
            std::cout << unicode_to_utf8(to_u32string(ast_head)) << std::endl;
            // Return results:
        }
        return {match, hit_end, match && hit_end, ast_head, positions};
    }

    ParseResultInfo parse(const std::string input) {
        return parse(unicode_from_utf8(input));
    }

}