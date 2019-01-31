#include<onerut_parser/unicode_support.hpp>
#include<onerut_parser/ast_x3.hpp>
#include<onerut_parser/ast_x3_to_chart.hpp>

namespace {
    // -------------------------------------------------------------------------
    // ------------- VISITOR ---------------------------------------------------
    // -------------------------------------------------------------------------

    struct to_chart_visitor {
        typedef void result_type;
        to_chart_visitor(
                const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
                unsigned deepness,
                onerut_parser::LinesInfo& chart
                );
        const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions;
        const unsigned deepness;
        onerut_parser::LinesInfo& chart;
        template<typename T>
        result_type operator()(const T & info);
    };

    to_chart_visitor::to_chart_visitor(
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            onerut_parser::LinesInfo& chart
            ) :
    positions(positions),
    deepness(deepness),
    chart(chart) {
    }

    template<typename T>
    to_chart_visitor::result_type to_chart_visitor::operator()(const T & info) {
        to_chart(info, positions, deepness, chart);
    }

}

namespace onerut_parser::onerut_ast::x3 {

    // -------------------------------------------------------------------------
    // ------------- HELPER GENERIC TEMPLATEW ----------------------------------
    // -------------------------------------------------------------------------

    template<class InfoT>
    void to_chart_common_implementation(
            const InfoT& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        while (chart.size() <= deepness)
            chart.emplace_back();
        chart[deepness].push_back({positions.position_of(info).begin(), positions.position_of(info).end()});
    }

    // -------------------------------------------------------------------------
    // -------------- FUNCTIONS FOR CONCRETE AST TYPES -------------------------
    // -------------------------------------------------------------------------

    void to_chart(
            const ExpressionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.assign, positions, deepness + 1, chart);
    }

    void to_chart(
            const OpAssignInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        if (info.bit)
            to_chart((*info.bit).identifier, positions, deepness + 1, chart);
        to_chart(info.sum, positions, deepness + 1, chart);
    }

    void to_chart(
            const OpPlusMinusInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.first_arg, positions, deepness + 1, chart);
        for (const OpPlusMinusBitInfo& arg_info : info.other_argv)
            to_chart(arg_info.arg, positions, deepness + 1, chart);
    }

    void to_chart(
            const OpProdDivInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.first_arg, positions, deepness + 1, chart);
        for (const OpProdDivBitInfo& arg_info : info.other_argv)
            to_chart(arg_info.arg, positions, deepness + 1, chart);
    }

    void to_chart(
            const OpPowInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.first_arg, positions, deepness + 1, chart);
        if (info.other_arg)
            to_chart(*info.other_arg, positions, deepness + 1, chart);
    }

    void to_chart(
            const OpAtInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.first_arg, positions, deepness + 1, chart);
        if (info.other_arg)
            to_chart(*info.other_arg, positions, deepness + 1, chart);
    }

    void to_chart(
            const OpArrowInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.first_arg, positions, deepness + 1, chart);
        if (info.other_arg)
            to_chart(*info.other_arg, positions, deepness + 1, chart);
    }

    void to_chart(
            const OpGlueInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.first_arg, positions, deepness + 1, chart);
        if (info.other_arg)
            to_chart(*info.other_arg, positions, deepness + 1, chart);
    }

    void to_chart(
            const Value1Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        auto visitor = to_chart_visitor(positions, deepness, chart);
        return boost::apply_visitor(visitor, info);
    }

    void to_chart(
            const LitDoubleInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
    }

    void to_chart(
            const LitLongInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
    }

    void to_chart(
            const OpUnaryPlusMinusInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.expression, positions, deepness + 1, chart);
    }

    void to_chart(
            const Value2Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        auto visitor = to_chart_visitor(positions, deepness, chart);
        return boost::apply_visitor(visitor, info);
    }

    void to_chart(
            const FunctionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        for (const ExpressionInfo& arg_info : info.argv)
            to_chart(arg_info, positions, deepness + 1, chart);
    }

    void to_chart(
            const IdentifierInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
    }

    void to_chart(
            const NestedExpression1Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.expression, positions, deepness + 1, chart);
    }

    void to_chart(const NestedExpression2Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            LinesInfo& chart) {
        to_chart_common_implementation(info, positions, deepness, chart);
        to_chart(info.expression, positions, deepness + 1, chart);
    }

    // -------------------------------------------------------------------------
    // ---------------   EASY API TO CREATE THE CHART  -------------------------
    // -------------------------------------------------------------------------    

    LinesInfo to_chart(
            const ExpressionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        LinesInfo chart;
        to_chart(info, positions, 0, chart);
        return chart;
    }

}