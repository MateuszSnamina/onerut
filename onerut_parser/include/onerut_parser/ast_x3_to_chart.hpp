#ifndef ONERUT_PARSER_AST_X3_TO_CHART
#define ONERUT_PARSER_AST_X3_TO_CHART

#include<onerut_parser/ast_x3.hpp>
#include<onerut_parser/print_chart.hpp>

namespace onerut_parser::onerut_ast::x3 {

    void to_chart(
            const ExpressionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    //void to_chart(const OpPlusInfo& info,
    //        const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
    //        unsigned deepness,
    //        LinesInfo& chart);
    void to_chart(
            const OpPlusMinusInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const OpProdDivInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const OpPowInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const OpAtInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const OpArrowInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const OpGlueInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const Value1Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const LitDoubleInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const LitIntInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);    
    void to_chart(
            const OpUnaryPlusMinusInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const Value2Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const FunctionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const IdentifierInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const NestedExpression1Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);
    void to_chart(
            const NestedExpression2Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart);

    LinesInfo to_chart(
            const ExpressionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

}

#endif