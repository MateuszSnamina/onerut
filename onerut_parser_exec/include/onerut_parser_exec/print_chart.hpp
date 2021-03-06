#ifndef ONERUT_PARSER_EXEC_PRINT_CHART
#define ONERUT_PARSER_EXEC_PRINT_CHART

#include<memory>
#include<string>
#include<vector>

#include<string_utils/string_span.hpp>
#include<esc/esc_manip.hpp>

namespace onerut_parser_exec {

    extern const char32_t chart_fill_character_1;
    extern const char32_t chart_fill_character_2;
    extern const char32_t chart_fill_character_3;

    // -------------------------------------------------------------------------
    // -------------- STYLED VERSION OF PRINT CHART ----------------------------
    // -------------------------------------------------------------------------

    struct BitChartInfo {
        string_utils::string_const_span span;
        esc::EscData esc_data;
    };

    //--------------------------------------------------------------------------
    
    using LineChartInfo = std::vector<BitChartInfo>;
    using LinesChartInfo = std::vector<LineChartInfo>;

    void print_ast_chart(
            std::ostream& stream,
            std::shared_ptr<const std::string> input,
            const LinesChartInfo& lines_info,
            std::string line_prefix = "");

    void print_styled_ast_chart_example();

    //--------------------------------------------------------------------------

    struct ErrorChartInfo {
        const string_utils::string_const_span span;
        const std::string message;
    };

    using ErrorsChartInfo = std::vector<ErrorChartInfo>;

    void print_errors_chart(
            std::ostream& stream,
            std::shared_ptr<const std::string> input,
            const ErrorsChartInfo& errors_info,
            std::string line_prefix = "");

}

#endif