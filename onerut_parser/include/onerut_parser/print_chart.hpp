#ifndef ONERUT_PARSER_PRINT_CHART
#define ONERUT_PARSER_PRINT_CHART

#include<memory>
#include<string>
#include<vector>

#include<string_utils/string_span.hpp>
#include<esc/esc_manip.hpp>

namespace onerut_parser {

    // -------------------------------------------------------------------------
    extern const char32_t chart_fill_character_1;
    extern const char32_t chart_fill_character_2;
    extern const char32_t chart_fill_character_3;

    // -------------------------------------------------------------------------
    // -------------- BASIC VERSION OF PRINT CHART -----------------------------
    // -------------------------------------------------------------------------    

    using LineBitInfo = string_const_span;
    using LineInfo = std::vector<LineBitInfo>;
    using LinesInfo = std::vector<LineInfo>;

    void print_chart(
            std::shared_ptr<const std::string> input,
            const LinesInfo&chart);
    
    // -------------------------------------------------------------------------
    // -------------- STYLED VERSION OF PRINT CHART ----------------------------
    // -------------------------------------------------------------------------

    struct LineBitStyledChartInfo {
        string_const_span span;
        esc::EscData esc_data;
    };

    using LineStyledChartInfo = std::vector<LineBitStyledChartInfo>;
    using LinesStyledChartInfo = std::vector<LineStyledChartInfo>;

    void print_chart(
            std::shared_ptr<const std::string> input,
            const LinesStyledChartInfo&chart);

    void print_styled_chart_example();
}

#endif