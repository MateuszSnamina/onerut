#include<cassert>
#include<iostream>

#include<string_utils/unicode_support.hpp>
#include<string_utils/greek_support.hpp>
#include<onerut_parser_exec/print_chart.hpp>

namespace onerut_parser_exec {

    extern const char32_t chart_fill_character_1 = U'░';
    extern const char32_t chart_fill_character_2 = U'▒';
    extern const char32_t chart_fill_character_3 = U'▓';

    // -------------------------------------------------------------------------
    // -------------- STYLED VERSION OF PRINT CHART ----------------------------
    // -------------------------------------------------------------------------

    void print_ast_chart(
            std::ostream& stream,
            std::shared_ptr<const std::string> input,
            const LinesChartInfo& lines_info,
            std::string line_prefix) {
        // Check input consistency:
        assert(input);
        for (const auto & line_info : lines_info) {
            auto it = input->cbegin();
            for (const auto & style_bit : line_info) {
                assert(style_bit.span.begin() <= style_bit.span.end());
                assert(input->cbegin() <= style_bit.span.begin());
                assert(style_bit.span.end() <= input->cend());
                assert(it <= style_bit.span.begin());
                it = style_bit.span.end();
            }
        }
        // Print:
        const unsigned inpit_number_of_visible_characters = string_utils::to_greek_number_of_visible_characters_in_result(*input);
        const std::u32string table_horizontal_line(inpit_number_of_visible_characters + 2, U'▓');
        stream << line_prefix << string_utils::unicode_to_utf8(table_horizontal_line) << std::endl;
        stream << line_prefix << "▓" << string_utils::StreamToGreek(*input) << "▓" << std::endl;
        stream << line_prefix << string_utils::unicode_to_utf8(table_horizontal_line) << std::endl;
        for (const auto & line_line : lines_info) {
            stream << line_prefix << "▓";
            auto it = input->cbegin();
            for (const auto & style_info : line_line) {
                {
                    const std::string_view text_view = string_utils::to_string_view(it, style_info.span.begin());
                    const unsigned number_of_visible_characters = string_utils::to_greek_number_of_visible_characters_in_result(text_view);
                    const std::u32string text_bit = std::u32string(number_of_visible_characters, chart_fill_character_1);
                    stream << string_utils::unicode_to_utf8(text_bit);
                }
                {
                    const auto text_view = string_utils::to_string_view(style_info.span);
                    stream << style_info.esc_data << string_utils::StreamToGreek(text_view);
                }
                it = style_info.span.end();
            }
            {
                const std::string_view text_view = string_utils::to_string_view(it, input->cend());
                const unsigned number_of_visible_characters = string_utils::to_greek_number_of_visible_characters_in_result(text_view);
                const std::u32string text_bit = std::u32string(number_of_visible_characters, chart_fill_character_1);
                stream << string_utils::unicode_to_utf8(text_bit);
            }
            stream << "▓" << std::endl;
        }
        stream << line_prefix << string_utils::unicode_to_utf8(table_horizontal_line) << std::endl;
    }

    // -------------------------------------------------------------------------

    void print_errors_chart(
            std::ostream& stream,
            std::shared_ptr<const std::string> input,
            const ErrorsChartInfo& errors_info,
            std::string line_prefix) {
        assert(input);
        for (const auto & error_info : errors_info) {
            assert(error_info.span.begin() <= error_info.span.end());
            assert(input->cbegin() <= error_info.span.begin());
            assert(error_info.span.end() <= input->cend());
        }
        for (const auto & error_info : errors_info) {
            stream << line_prefix;
            const auto pre_text_view = string_utils::to_string_view(input->cbegin(), error_info.span.begin());
            const auto error_text_view = string_utils::to_string_view(error_info.span);
            const auto post_text_view = string_utils::to_string_view(error_info.span.end(), input->cend());
            stream << esc::manip::bg_gray << string_utils::StreamToGreek(pre_text_view) << esc::manip::reset;
            stream << esc::manip::bg_red << string_utils::StreamToGreek(error_text_view) << esc::manip::reset;
            stream << esc::manip::bg_gray << string_utils::StreamToGreek(post_text_view) << esc::manip::reset;
            stream << std::endl;
            stream << line_prefix;
            stream << esc::manip::red << error_info.message << esc::manip::reset;
            stream << std::endl;
        }
    }

    // -------------------------------------------------------------------------
    // -------------- STYLED VERSION OF PRINT CHART -- EXAMPLE  ----------------
    // -------------------------------------------------------------------------    

    void print_styled_ast_chart_example() {

        const auto input = std::make_shared<std::string>("123456789abcdef");
        const onerut_parser_exec::BitChartInfo bi0{
            {input->begin() + 2, input->begin() + 8},
            {esc::Color::Green, esc::Color::Auto, true, false, false}};

        const onerut_parser_exec::BitChartInfo bi1{
            {input->begin() + 2, input->begin() + 4},
            {esc::Color::Green, esc::Color::Auto, false, true, false}};

        const onerut_parser_exec::BitChartInfo bi2{
            {input->begin() + 6, input->begin() + 8},
            {esc::Color::Auto, esc::Color::Red, false, false, true}};

        const LineChartInfo l0{bi0};
        const LineChartInfo l1{bi1, bi2};
        const LinesChartInfo ls{l0, l1};

        print_ast_chart(std::cout, input, ls);
    }
}