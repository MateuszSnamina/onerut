#include<esc/esc_manip.hpp>

#include<onerut_parser_exec/ast_x3.hpp>
#include<onerut_parser_exec/ast_x3_to_chart.hpp>


namespace onerut_parser_exec::onerut_ast::x3 {

    namespace {

        // ---------------------------------------------------------------------
        // ------------- VISITOR -----------------------------------------------
        // ---------------------------------------------------------------------

        struct to_ast_chart_visitor {
            typedef void result_type;
            to_ast_chart_visitor(
                    const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
                    unsigned deepness,
                    LinesChartInfo& ast_chart
                    );
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions;
            const unsigned deepness;
            LinesChartInfo& ast_chart;
            template<typename T>
            result_type operator()(const T & info);
        };

        to_ast_chart_visitor::to_ast_chart_visitor(
                const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
                unsigned deepness,
                LinesChartInfo& ast_chart
                ) :
        positions(positions),
        deepness(deepness),
        ast_chart(ast_chart) {
        }

        template<typename T>
        to_ast_chart_visitor::result_type to_ast_chart_visitor::operator()(const T & info) {
            to_ast_chart(info, positions, deepness, ast_chart);
        }

    }

    // -------------------------------------------------------------------------
    // ------------- HELPER GENERIC TEMPLATEW ----------------------------------
    // -------------------------------------------------------------------------

    template<class InfoT>
    void to_ast_chart_common_implementation(
            const InfoT& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        while (ast_chart.size() <= deepness)
            ast_chart.emplace_back();
        const esc::EscData esc_data = esc::EscDataBuilder() << esc::manip::build_esc_data;
        const string_utils::string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        const BitChartInfo bit = {span, esc_data};
        ast_chart[deepness].push_back(bit);
    }

    // -------------------------------------------------------------------------
    // -------------- FUNCTIONS FOR CONCRETE AST TYPES -------------------------
    // -------------------------------------------------------------------------

    void to_ast_chart(
            const ExpressionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.assign, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const OpAssignInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        if (info.bit) {
            to_ast_chart((*info.bit).identifier, positions, deepness + 1, ast_chart);
        }
        to_ast_chart(info.expression, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const OpPlusMinusInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.first_arg, positions, deepness + 1, ast_chart);
        for (const OpPlusMinusBitInfo& arg_info : info.other_argv)
            to_ast_chart(arg_info.arg, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const OpProdDivInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.first_arg, positions, deepness + 1, ast_chart);
        for (const OpProdDivBitInfo& arg_info : info.other_argv)
            to_ast_chart(arg_info.arg, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const OpPowInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.first_arg, positions, deepness + 1, ast_chart);
        if (info.other_arg)
            to_ast_chart(*info.other_arg, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const OpAtInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.first_arg, positions, deepness + 1, ast_chart);
        if (info.other_arg)
            to_ast_chart(*info.other_arg, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const OpArrowInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.first_arg, positions, deepness + 1, ast_chart);
        if (info.other_arg)
            to_ast_chart(*info.other_arg, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const OpGlueInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.first_arg, positions, deepness + 1, ast_chart);
        if (info.other_arg)
            to_ast_chart(*info.other_arg, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const Value1Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        auto visitor = to_ast_chart_visitor(positions, deepness, ast_chart);
        return boost::apply_visitor(visitor, info);
    }

    void to_ast_chart(
            const LitDoubleInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
    }

    void to_ast_chart(
            const LitPureComplexDoubleInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
    }

    void to_ast_chart(
            const LitLongInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
    }

    void to_ast_chart(
            const OpUnaryPlusMinusInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.expression, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const Value2Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        auto visitor = to_ast_chart_visitor(positions, deepness, ast_chart);
        return boost::apply_visitor(visitor, info);
    }

    void to_ast_chart(
            const FunctionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        for (const ExpressionInfo& arg_info : info.argv)
            to_ast_chart(arg_info, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(
            const EmptyFunctionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
    }

    void to_ast_chart(
            const IdentifierInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
    }

    void to_ast_chart(
            const NestedExpression1Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.expression, positions, deepness + 1, ast_chart);
    }

    void to_ast_chart(const NestedExpression2Info& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions,
            unsigned deepness,
            LinesChartInfo& ast_chart) {
        to_ast_chart_common_implementation(info, positions, deepness, ast_chart);
        to_ast_chart(info.expression, positions, deepness + 1, ast_chart);
    }

    // -------------------------------------------------------------------------
    // ---------------   EASY API TO CREATE THE CHART  -------------------------
    // -------------------------------------------------------------------------    

    LinesChartInfo to_ast_chart(
            const ExpressionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        LinesChartInfo ast_chart;
        to_ast_chart(info, positions, 0, ast_chart);
        return ast_chart;
    }

}