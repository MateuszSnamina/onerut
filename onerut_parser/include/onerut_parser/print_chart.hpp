#ifndef ONERUT_PARSER_PRINT_CHART
#define ONERUT_PARSER_PRINT_CHART

#include<memory>
#include<string>
#include<vector>

#include<onerut_parser/string_span.hpp>
#include<esc/esc_manip.hpp>

namespace onerut_parser {

    void print_chart(
            std::shared_ptr<const std::u32string> input,
            const std::vector<std::u32string>& chart);

    struct ChartStyleInfo {
        u32string_const_span span;
        esc::EscData esc_data;
    };

    void print_chart(
            std::shared_ptr<const std::u32string> input,
            const std::vector<std::u32string>& chart,
            const std::vector<std::vector<ChartStyleInfo>>&style);

}

#endif