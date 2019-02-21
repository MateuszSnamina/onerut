#include<iostream>
#include<memory>
#include<boost/spirit/home/x3.hpp>
#include<boost/spirit/home/x3/support/ast/variant.hpp>
#include<boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include<boost/spirit/home/x3/support/utility/error_reporting.hpp>
//#include<boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include<boost/fusion/adapted/struct.hpp>

#include<onerut_parser/ast_x3.hpp>
#include<onerut_parser/ast_x3_to_oneliner.hpp>
#include<onerut_parser/ast_x3_to_chart.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/gramma_parser.hpp>

namespace onerut_parser {

    bool X3ParseResultInfo::hit_end() const {
        return it == input->cend();
    }

    bool X3ParseResultInfo::succes() const {
        return match && hit_end();
    }

    string_const_span X3ParseResultInfo::parsed_span() const {
        return{input->cbegin(), it};
    }

    string_const_span X3ParseResultInfo::not_parsed_span() const {
        return{it, input->cend()};
    }

}

// -----------------------------------------------------------------------------
// This has to be in the global scope:

BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::ExpressionInfo,
        (onerut_parser::onerut_ast::x3::OpAssignInfo, assign))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpAssignBitInfo,
        (bool, new_flag)
        (bool, const_flag)
        (onerut_parser::onerut_ast::x3::IdentifierInfo, identifier))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpAssignInfo,
        (boost::optional<onerut_parser::onerut_ast::x3::OpAssignBitInfo>, bit)
        (onerut_parser::onerut_ast::x3::OpPlusMinusInfo, sum))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpPlusMinusBitInfo,
        (char, op)
        (onerut_parser::onerut_ast::x3::OpProdDivInfo, arg))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpPlusMinusInfo,
        (onerut_parser::onerut_ast::x3::OpProdDivInfo, first_arg)
        (std::vector<onerut_parser::onerut_ast::x3::OpPlusMinusBitInfo>, other_argv))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpProdDivBitInfo,
        (char, op)
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
        (onerut_parser::onerut_ast::x3::Value1Info, first_arg)
        (boost::optional<onerut_parser::onerut_ast::x3::Value1Info>, other_arg))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::OpUnaryPlusMinusInfo,
        (boost::optional<char>, op)
        (onerut_parser::onerut_ast::x3::Value2Info, expression))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::LitPureComplexDoubleInfo,
        (double, value))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::LitDoubleInfo,
        (double, value))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::LitLongInfo,
        (long, value))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::FunctionInfo,
        (onerut_parser::onerut_ast::x3::IdentifierInfo, name)
        (std::vector<onerut_parser::onerut_ast::x3::ExpressionInfo>, argv))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::EmptyFunctionInfo,
        (onerut_parser::onerut_ast::x3::IdentifierInfo, name))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::IdentifierInfo,
        (char, first_char)
        (std::vector<char>, other_chars))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::NestedExpression1Info,
        (onerut_parser::onerut_ast::x3::ExpressionInfo, expression))
BOOST_FUSION_ADAPT_STRUCT(
        onerut_parser::onerut_ast::x3::NestedExpression2Info,
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
        error_handler(x.where(), message); // this prints to cerr.
        return boost::spirit::x3::error_handler_result::fail;
    }

}

// -----------------------------------------------------------------------------
namespace onerut_parser::onerut_gramma {

    struct ExpressionParserRaw : annotate_position {
    };

    struct ExpressionParser : annotate_position, error_handler {
    };

    struct OpAssignBitParser : annotate_position {
    };

    struct OpAssignParser : annotate_position {
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

    struct Value1Parser : annotate_position {
    };

    struct LitPureComplexDoubleParser : annotate_position {
    };

    struct LitDoubleParser : annotate_position {
    };

    struct LitLongParser : annotate_position {
    };

    struct OpUnaryPlusMinusParser : annotate_position {
    };

    struct Value2Parser : annotate_position {
    };

    struct FunctionParser : annotate_position {
    };

    struct EmptyFunctionParser : annotate_position {
    };

    struct IndentifierParser : annotate_position {
    };

    struct NestedExpression1Parser : annotate_position {
    };

    struct NestedExpression2Parser : annotate_position {
    };

    boost::spirit::x3::rule< ExpressionParserRaw, onerut_ast::x3::ExpressionInfo > const expression_parser_raw = "expression";
    boost::spirit::x3::rule< ExpressionParser, onerut_ast::x3::ExpressionInfo > const expression_parser = "expression";
    boost::spirit::x3::rule< OpAssignBitParser, onerut_ast::x3::OpAssignBitInfo > const op_assign_bit_parser = "op_assign_bit";
    boost::spirit::x3::rule< OpAssignParser, onerut_ast::x3::OpAssignInfo > const op_assign_parser = "op_assign";
    boost::spirit::x3::rule< OpPlusMinusBitParser, onerut_ast::x3::OpPlusMinusBitInfo > const op_plus_minus_bit_parser = "op_plus_minus_bit";
    boost::spirit::x3::rule< OpPlusMinusParser, onerut_ast::x3::OpPlusMinusInfo > const op_plus_minus_parser = "op_plus_minus";
    boost::spirit::x3::rule< OpProdDivBitParser, onerut_ast::x3::OpProdDivBitInfo > const op_prod_div_bit_parser = "op_prod_div_bit";
    boost::spirit::x3::rule< OpProdDivParser, onerut_ast::x3::OpProdDivInfo > const op_prod_div_parser = "op_prod_div";
    boost::spirit::x3::rule< OpPowParser, onerut_ast::x3::OpPowInfo> const op_pow_parser = "op_pow";
    boost::spirit::x3::rule< OpAtParser, onerut_ast::x3::OpAtInfo> const op_at_parser = "op_at";
    boost::spirit::x3::rule< OpArrowParser, onerut_ast::x3::OpArrowInfo> const op_arrow_parser = "op_arrow";
    boost::spirit::x3::rule< OpGlueParser, onerut_ast::x3::OpGlueInfo> const op_glue_parser = "op_glue";

    boost::spirit::x3::rule< Value1Parser, onerut_ast::x3::Value1Info > const value1_parser = "value1";
    boost::spirit::x3::rule< LitPureComplexDoubleParser, onerut_ast::x3::LitPureComplexDoubleInfo > const lit_pure_complex_double_parser = "lit_pure_complex_double";
    boost::spirit::x3::rule< LitDoubleParser, onerut_ast::x3::LitDoubleInfo > const lit_double_parser = "lit_double";
    boost::spirit::x3::rule< LitLongParser, onerut_ast::x3::LitLongInfo > const lit_long_parser = "lit_long";
    boost::spirit::x3::rule< OpUnaryPlusMinusParser, onerut_ast::x3::OpUnaryPlusMinusInfo > const op_unary_plus_minus_parser = "unary_plus_minus";

    boost::spirit::x3::rule< Value2Parser, onerut_ast::x3::Value2Info > const value2_parser = "value2";
    boost::spirit::x3::rule< FunctionParser, onerut_ast::x3::FunctionInfo > const function_parser = "function";
    boost::spirit::x3::rule< EmptyFunctionParser, onerut_ast::x3::EmptyFunctionInfo > const empty_function_parser = "empty_function";
    boost::spirit::x3::rule< IndentifierParser, onerut_ast::x3::IdentifierInfo > const indentifier_parser = "indentifier";
    boost::spirit::x3::rule< NestedExpression1Parser, onerut_ast::x3::NestedExpression1Info > const nested_expression1_parser = "nested_expression";
    boost::spirit::x3::rule< NestedExpression2Parser, onerut_ast::x3::NestedExpression2Info > const nested_expression2_parser = "nested_expression";

    // https://en.wikipedia.org/wiki/Parsing_expression_grammar:

    //auto const expression_parser_raw_def = op_plus_minus_parser;
    auto const expression_parser_raw_def = op_assign_parser;
    auto const expression_parser_def = boost::spirit::x3::expect[expression_parser_raw];
    auto const op_assign_bit_parser_def = boost::spirit::x3::matches["new"] >> boost::spirit::x3::matches["const"] >> indentifier_parser >> ":=";
    auto const op_assign_parser_def = -op_assign_bit_parser >> op_plus_minus_parser;
    auto const op_plus_minus_bit_parser_def = boost::spirit::x3::char_("+-") >> op_prod_div_parser;
    auto const op_plus_minus_parser_def = op_prod_div_parser >> *(op_plus_minus_bit_parser);
    auto const op_prod_div_bit_parser_def = boost::spirit::x3::char_("/*") >> op_pow_parser;
    auto const op_prod_div_parser_def = op_pow_parser >> *(op_prod_div_bit_parser);
    auto const op_pow_parser_def = op_at_parser >> -("^" >> op_at_parser);
    auto const op_at_parser_def = op_arrow_parser>> -("@" >> op_arrow_parser);
    auto const op_arrow_parser_def = op_glue_parser>> -("->" >> op_glue_parser);
    auto const op_glue_parser_def = value1_parser>> -("::" >> value1_parser);
    auto const value1_parser_def =
            lit_pure_complex_double_parser | lit_double_parser | lit_long_parser | // Note: lit_double_parser has to be before lit_long_parser.
            op_unary_plus_minus_parser;
    auto const op_unary_plus_minus_parser_def = -boost::spirit::x3::char_("+-") >> value2_parser;
    auto const value2_parser_def =
            empty_function_parser | function_parser | indentifier_parser | // Note: function_parser has to be before indentifier_parser.
            nested_expression1_parser | nested_expression2_parser;
    auto const lit_pure_complex_double_parser_def = boost::spirit::x3::lexeme[ boost::spirit::x3::double_ >> 'i' ];
    auto const lit_double_parser_def = boost::spirit::x3::real_parser<double, boost::spirit::x3::strict_real_policies<double>>();
    auto const lit_long_parser_def = boost::spirit::x3::long_;
    auto const function_parser_def = indentifier_parser >> '(' >> expression_parser % ',' >> ')';
    auto const empty_function_parser_def = indentifier_parser >> '(' >> ')';
    auto const indentifier_parser_def = boost::spirit::x3::lexeme[boost::spirit::x3::char_("A-Za-z_") >> *boost::spirit::x3::char_("A-Za-z1-9_")];
    auto const nested_expression1_parser_def = '(' >> expression_parser >> ')';
    auto const nested_expression2_parser_def = '[' >> expression_parser >> ']';

    BOOST_SPIRIT_DEFINE(
            expression_parser_raw,
            expression_parser,
            op_assign_bit_parser,
            op_assign_parser,
            op_plus_minus_bit_parser,
            op_plus_minus_parser,
            op_prod_div_bit_parser,
            op_prod_div_parser,
            op_pow_parser,
            op_at_parser,
            op_arrow_parser,
            op_glue_parser,
            value1_parser,
            lit_pure_complex_double_parser, lit_double_parser, lit_long_parser,
            op_unary_plus_minus_parser,
            value2_parser,
            function_parser, empty_function_parser, indentifier_parser,
            nested_expression1_parser,
            nested_expression2_parser
            )

}

// -----------------------------------------------------------------------------

namespace onerut_parser {

    X3ParseResultInfo parse(std::shared_ptr<const std::string> input) {
        // Iterators:
        const std::string::const_iterator input_begin = input->cbegin();
        const std::string::const_iterator input_end = input->cend();
        std::string::const_iterator it = input_begin;
        // Results:
        onerut_parser::onerut_ast::x3::ExpressionInfo ast_head;
        boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >> positions(input_begin, input_end);
        // Annotation, positions_handlers, error_handlers:
        boost::spirit::x3::error_handler<std::string::const_iterator> error_handler(it, input_end, std::cerr);
        // The Parser, parse:
        auto const parser =
                boost::spirit::x3::with<boost::spirit::x3::error_handler_tag>(std::ref(error_handler))[
                boost::spirit::x3::with<position_cache_tag>(std::ref(positions))[
                onerut_parser::onerut_gramma::expression_parser
                ]];
        const bool match = phrase_parse(it, input_end, parser, boost::spirit::x3::ascii::space, ast_head);
        //const bool hit_end = (it == input_end);
        // Return results:        
        return {input, it, match, ast_head, positions};
    }

    //    X3ParseResultInfo parse(const std::string input) {
    //        return parse(std::make_shared<const std::string>(input));
    //    }

    void print(X3ParseResultInfo info) {
        std::cout << "match:     " << info.match << std::endl;
        std::cout << "hit_end:   " << info.hit_end() << std::endl;
        if (info.match) {
            std::cout << "to_oneliner: " << to_oneliner(info.ast_head) << std::endl;
            const auto& ast_chart = to_ast_chart(info.ast_head, info.positions);
            print_ast_chart(info.input, ast_chart);
        }
    }
}