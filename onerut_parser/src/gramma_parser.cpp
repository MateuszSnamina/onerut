#include<iostream>
#include<memory>
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
        onerut_parser::onerut_ast::x3::ExpressionInfo,
        (onerut_parser::onerut_ast::x3::OpPlusMinusInfo, sum))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpPlusMinusBitInfo,
        (char32_t, op)
        (onerut_parser::onerut_ast::x3::OpProdDivInfo, arg))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpPlusMinusInfo,
        (onerut_parser::onerut_ast::x3::OpProdDivInfo, first_arg)
        (std::vector<onerut_parser::onerut_ast::x3::OpPlusMinusBitInfo>, other_argv))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpProdDivBitInfo,
        (char32_t, op)
        (onerut_parser::onerut_ast::x3::OpPowInfo, arg))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpProdDivInfo,
        (onerut_parser::onerut_ast::x3::OpPowInfo, first_arg)
        (std::vector<onerut_parser::onerut_ast::x3::OpProdDivBitInfo>, other_argv))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpPowInfo,
        (onerut_parser::onerut_ast::x3::OpAtInfo, first_arg)
        (boost::optional<onerut_parser::onerut_ast::x3::OpAtInfo>, other_arg))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpAtInfo,
        (onerut_parser::onerut_ast::x3::OpArrowInfo, first_arg)
        (boost::optional<onerut_parser::onerut_ast::x3::OpArrowInfo>, other_arg))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpArrowInfo,
        (onerut_parser::onerut_ast::x3::OpGlueInfo, first_arg)
        (boost::optional<onerut_parser::onerut_ast::x3::OpGlueInfo>, other_arg))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpGlueInfo,
        (onerut_parser::onerut_ast::x3::ValueInfo, first_arg)
        (boost::optional<onerut_parser::onerut_ast::x3::ValueInfo>, other_arg))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::LitDoubleInfo,
        (double, value))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::LitIntInfo,
        (int, value))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::FunctionInfo,
        (onerut_parser::onerut_ast::x3::IdentifierInfo, name)
        (std::vector<onerut_parser::onerut_ast::x3::ExpressionInfo>, argv))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::IdentifierInfo,
        (char32_t, first_char)
        (std::vector<char32_t>, other_chars))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::NestedExpressionInfo,
        (onerut_parser::onerut_ast::x3::ExpressionInfo, expression))

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

    struct ExpressionParserRaw : annotate_position {
    };

    struct ExpressionParser : annotate_position, error_handler {
    };

    struct OpPlusMinusBitParser : annotate_position {
    };

    struct OpPlusMinusParser : annotate_position {
    };

    struct OpProdDivBitParser : annotate_position {
    };

    struct OpProdDivParser : annotate_position {
    };

    struct OpGlueParser : annotate_position {
    };

    struct OpArrowParser : annotate_position {
    };

    struct OpAtParser : annotate_position {
    };

    struct OpPowParser : annotate_position {
    };

    struct ValueParser : annotate_position {
    };

    struct LitDoubleParser : annotate_position {
    };

    struct LitIntParser : annotate_position {
    };

    struct FunctionParser : annotate_position {
    };

    struct IndentifierParser : annotate_position {
    };

    struct NestedExpressionParser : annotate_position {
    };

    boost::spirit::x3::rule<class ExpressionParserRaw, onerut_ast::x3::ExpressionInfo > const expression_parser_raw = "expression_raw";
    boost::spirit::x3::rule<class ExpressionParser, onerut_ast::x3::ExpressionInfo > const expression_parser = "expression";

    boost::spirit::x3::rule<class OpPlusMinusBitParser, onerut_ast::x3::OpPlusMinusBitInfo > const op_plus_minus_bit_parser = "op_plus_minus_bit";
    boost::spirit::x3::rule<class OpPlusMinusParser, onerut_ast::x3::OpPlusMinusInfo > const op_plus_minus_parser = "op_plus_minus";

    boost::spirit::x3::rule<class OpProdDivBitParser, onerut_ast::x3::OpProdDivBitInfo > const op_prod_div_bit_parser = "op_prod_div_bit";
    boost::spirit::x3::rule<class OpProdDivParser, onerut_ast::x3::OpProdDivInfo > const op_prod_div_parser = "op_prod_div";

    boost::spirit::x3::rule<class OpPowParser, onerut_ast::x3::OpPowInfo> const op_pow_parser = "op_pow";
    boost::spirit::x3::rule<class OpAtParser, onerut_ast::x3::OpAtInfo> const op_at_parser = "op_at";
    boost::spirit::x3::rule<class OpArrowParser, onerut_ast::x3::OpArrowInfo> const op_arrow_parser = "op_arrow";
    boost::spirit::x3::rule<class OpGlueParser, onerut_ast::x3::OpGlueInfo> const op_glue_parser = "op_glue";

    boost::spirit::x3::rule<class ValueParser, onerut_ast::x3::ValueInfo > const value_parser = "value";
    boost::spirit::x3::rule<class LitDoubleParser, onerut_ast::x3::LitDoubleInfo > const lit_double_parser = "lit_double";
    boost::spirit::x3::rule<class LitIntParser, onerut_ast::x3::LitIntInfo > const lit_int_parser = "lit_int";
    boost::spirit::x3::rule<class FunctionParser, onerut_ast::x3::FunctionInfo > const function_parser = "function";
    boost::spirit::x3::rule<class IndentifierParser, onerut_ast::x3::IdentifierInfo > const indentifier_parser = "indentifier";
    boost::spirit::x3::rule<class NestedExpressionParser, onerut_ast::x3::NestedExpressionInfo > const nested_expression_parser = "nested_expression";

    // https://en.wikipedia.org/wiki/Parsing_expression_grammar:

    //auto const expression_parser_raw_def = op_plus_parser;
    auto const expression_parser_raw_def = op_plus_minus_parser;
    auto const expression_parser_def = boost::spirit::x3::expect[expression_parser_raw];
    auto const op_plus_minus_bit_parser_def = boost::spirit::x3::char_("+-") >> op_prod_div_parser;
    auto const op_plus_minus_parser_def = op_prod_div_parser >> *(op_plus_minus_bit_parser);
    auto const op_prod_div_bit_parser_def = boost::spirit::x3::char_("/*") >> op_pow_parser;
    auto const op_prod_div_parser_def = op_pow_parser >> *(op_prod_div_bit_parser);

    auto const op_pow_parser_def = op_at_parser >> -("^" >> op_at_parser);
    auto const op_at_parser_def = op_arrow_parser>> -("@" >> op_arrow_parser);
    auto const op_arrow_parser_def = op_glue_parser>> -("->" >> op_glue_parser);
    auto const op_glue_parser_def = value_parser>> -("::" >> value_parser);

    auto const value_parser_def =
            lit_double_parser | lit_int_parser | // Note: lit_double_parser has to be before lit_int_parser.
            function_parser | indentifier_parser | //Note: function_parser has to be before indentifier_parser.
            nested_expression_parser;
    auto const lit_double_parser_def = boost::spirit::x3::real_parser<double, boost::spirit::x3::strict_real_policies<double>>();
    auto const lit_int_parser_def = boost::spirit::x3::int_;
    auto const function_parser_def = indentifier_parser >> '(' >> expression_parser % ',' >> ')';
    auto const indentifier_parser_def = boost::spirit::x3::lexeme[boost::spirit::x3::char_("A-Za-z_") >> *boost::spirit::x3::char_("A-Za-z1-9_")];
    auto const nested_expression_parser_def = '(' >> expression_parser >> ')';

    BOOST_SPIRIT_DEFINE(
            expression_parser_raw,
            expression_parser,
            op_plus_minus_bit_parser,
            op_plus_minus_parser,
            op_prod_div_bit_parser,
            op_prod_div_parser,
            op_pow_parser,
            op_at_parser,
            op_arrow_parser,
            op_glue_parser,
            value_parser,
            lit_double_parser, lit_int_parser,
            function_parser, indentifier_parser,
            nested_expression_parser)

}

// -----------------------------------------------------------------------------

namespace onerut_parser {

    ParseResultInfo parse(std::shared_ptr<const std::u32string> input) {
        // Iterators:
        const std::u32string::const_iterator input_begin = input->cbegin();
        const std::u32string::const_iterator input_end = input->cend();
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
        const bool match = phrase_parse(it, input_end, parser, boost::spirit::x3::ascii::space, ast_head);
        //const bool match = false; //debug
        const bool hit_end = (it == input_end);
        // Return results:        
        return {input, match, hit_end, match && hit_end, ast_head, positions};
    }

    ParseResultInfo parse(const std::u32string input) {
        return parse(std::make_shared<const std::u32string>(input));
    }

    ParseResultInfo parse(const std::string input) {
        return parse(std::make_shared<const std::u32string>(unicode_from_utf8(input)));
    }

    void print(ParseResultInfo info) {
        std::cout << "match:     " << info.match << std::endl;
        std::cout << "hit_end:   " << info.hit_end << std::endl;
        if (info.match) {
            std::cout << "to_string: " << unicode_to_utf8(to_u32string(info.ast_head)) << std::endl;
            std::vector<std::u32string> chart = to_u32string_chart(info.ast_head, info.positions);
            const unsigned input_length = info.positions.last() - info.positions.first();
            const std::u32string table_horizontal_line(input_length + 2, U'▓');
            std::cout << unicode_to_utf8(table_horizontal_line) << std::endl;
            std::cout << "▓" << unicode_to_utf8(*info.input) << "▓" << std::endl;
            std::cout << unicode_to_utf8(table_horizontal_line) << std::endl;
            for (const auto & chart_line : chart)
                std::cout << "▓" << unicode_to_utf8(chart_line) << "▓" << std::endl;
            std::cout << unicode_to_utf8(table_horizontal_line) << std::endl;
        }
    }
}