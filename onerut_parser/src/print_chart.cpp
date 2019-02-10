#include<cassert>
#include<iostream>

#include<string_utils/unicode_support.hpp>
#include<onerut_parser/print_chart.hpp>

namespace onerut_parser {

    extern const char32_t chart_fill_character_1 = U'░';
    extern const char32_t chart_fill_character_2 = U'▒';
    extern const char32_t chart_fill_character_3 = U'▓';

    // -------------------------------------------------------------------------
    // -------------- STYLED VERSION OF PRINT CHART ----------------------------
    // -------------------------------------------------------------------------

    void print_chart(
            std::shared_ptr<const std::string> input,
            const LinesStyledChartInfo&chart,
            std::string line_prefix) {
        // Check input consistency:
        assert(input);
        for (const auto & chart_line : chart) {
            auto it = input->cbegin();
            for (const auto & style_bit : chart_line) {
                assert(style_bit.span.begin() <= style_bit.span.end());
                assert(input->cbegin() <= style_bit.span.begin());
                assert(style_bit.span.end() <= input->cend());
                assert(it <= style_bit.span.begin());
                it = style_bit.span.end();
            }
        }
        // Print:
        const std::u32string table_horizontal_line(input->size() + 2, U'▓');
        std::cout << line_prefix << unicode_to_utf8(table_horizontal_line) << std::endl;
        std::cout << line_prefix << "▓" << *input << "▓" << std::endl;
        std::cout << line_prefix << unicode_to_utf8(table_horizontal_line) << std::endl;
        for (const auto & chart_line : chart) {
            std::cout << line_prefix << "▓";
            auto it = input->cbegin();
            for (const auto & style_bit : chart_line) {
                {
                    const unsigned length = style_bit.span.begin() - it;
                    const std::u32string text_bit = std::u32string(length, chart_fill_character_1);
                    std::cout << unicode_to_utf8(text_bit);
                }
                {
                    const auto text_view = to_string_view(style_bit.span);
                    std::cout << style_bit.esc_data << text_view;
                }
                it = style_bit.span.end();
            }
            {
                const unsigned length = input->cend() - it;
                const std::u32string text_bit = std::u32string(length, chart_fill_character_1);
                std::cout << unicode_to_utf8(text_bit);
            }
            std::cout << "▓" << std::endl;
        }
        std::cout << line_prefix << unicode_to_utf8(table_horizontal_line) << std::endl;
    }

    // -------------------------------------------------------------------------
    // -------------- STYLED VERSION OF PRINT CHART ----------------------------
    // -------------------------------------------------------------------------    

    void print_styled_chart_example() {

        const auto input = std::make_shared<std::string>("123456789abcdef");
        const onerut_parser::LineBitStyledChartInfo bi0{
            {input->begin() + 2, input->begin() + 8},
            {esc::Color::Green, esc::Color::Auto, true, false, false}};

        const onerut_parser::LineBitStyledChartInfo bi1{
            {input->begin() + 2, input->begin() + 4},
            {esc::Color::Green, esc::Color::Auto, false, true, false}};

        const onerut_parser::LineBitStyledChartInfo bi2{
            {input->begin() + 6, input->begin() + 8},
            {esc::Color::Auto, esc::Color::Red, false, false, true}};

        const LineStyledChartInfo l0{bi0};
        const LineStyledChartInfo l1{bi1, bi2};
        const LinesStyledChartInfo ls{l0, l1};

        print_chart(input, ls);
    }
}