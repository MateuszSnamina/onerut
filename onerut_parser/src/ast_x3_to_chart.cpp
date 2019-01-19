#include<onerut_parser/ast_x3.hpp>
#include<onerut_parser/unicode_support.hpp>

namespace onerut_parser::onerut_ast::x3 {

    extern const char32_t chart_fill_character_1 = U'░';
    extern const char32_t chart_fill_character_2 = U'▒';
    extern const char32_t chart_fill_character_3 = U'▓';

    // -------------------------------------------------------------------------
    // ------------- VISITOR ---------------------------------------------------
    // -------------------------------------------------------------------------

    struct to_string_chart_visitor {
        typedef void result_type;
        to_string_chart_visitor(
                const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
                unsigned deepness,
                std::vector<std::u32string>& chart
                );
        const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions;
        unsigned deepness;
        std::vector<std::u32string>& chart;
        template<typename T>
        result_type operator()(const T & info);
    };

    to_string_chart_visitor::to_string_chart_visitor(
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::u32string>& chart
            ) :
    positions(positions),
    deepness(deepness),
    chart(chart) {
    }

    template<typename T>
    to_string_chart_visitor::result_type to_string_chart_visitor::operator()(const T & info) {
        to_u32string_chart(info, positions, deepness, chart);
    }

    // -------------------------------------------------------------------------
    // ------------- FUNCTIONS FOR EXPRESSION ----------------------------------
    // -------------------------------------------------------------------------

    void to_u32string_chart(
            const ExpressionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::u32string>& chart) {
        auto visitor = to_string_chart_visitor(positions, deepness, chart);
        return boost::apply_visitor(visitor, info);
    }

    // -------------------------------------------------------------------------
    // ------------- FUNCTIONS FOR CONCRETE EXPRESSION TYPES -------------------
    // -------------------------------------------------------------------------

    void to_u32string_chart(
            const IdentifierInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::u32string>& chart) {
        while (chart.size() <= deepness)
            chart.emplace_back(positions.last() - positions.first(), chart_fill_character_1);
        const unsigned offset = positions.position_of(info).begin() - positions.first();
        std::copy(positions.position_of(info).begin(), positions.position_of(info).end(), chart[deepness].begin() + offset);
    }

    void to_u32string_chart(
            const LitIntInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::u32string>& chart) {
        while (chart.size() <= deepness)
            chart.emplace_back(positions.last() - positions.first(), chart_fill_character_1);
        const unsigned offset = positions.position_of(info).begin() - positions.first();
        std::copy(positions.position_of(info).begin(), positions.position_of(info).end(), chart[deepness].begin() + offset);
    }

    void to_u32string_chart(
            const LitDoubleInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::u32string>& chart) {
        while (chart.size() <= deepness)
            chart.emplace_back(positions.last() - positions.first(), chart_fill_character_1);
        const unsigned offset = positions.position_of(info).begin() - positions.first();
        std::copy(positions.position_of(info).begin(), positions.position_of(info).end(), chart[deepness].begin() + offset);
    }

    void to_u32string_chart(
            const FunctionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::u32string>& chart) {
        while (chart.size() <= deepness)
            chart.emplace_back(positions.last() - positions.first(), chart_fill_character_1);
        const unsigned offset = positions.position_of(info).begin() - positions.first();
        std::copy(positions.position_of(info).begin(), positions.position_of(info).end(), chart[deepness].begin() + offset);
        for (const ExpressionInfo& arg_info : info.argv) {
            to_u32string_chart(arg_info, positions, deepness + 1, chart);
        }
    }

    // -------------------------------------------------------------------------
    // ---------------   EASY API TO CREATE THE CHART  -------------------------
    // -------------------------------------------------------------------------    

    std::vector<std::u32string> to_u32string_chart(
            const ExpressionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        std::vector<std::u32string> chart;
        to_string_chart_visitor visitor(positions, 0, chart);
        boost::apply_visitor(visitor, info);
        return chart;
    }

}