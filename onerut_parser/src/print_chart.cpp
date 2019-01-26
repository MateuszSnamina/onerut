#include<cassert>
#include<iostream>

#include<onerut_parser/unicode_support.hpp>
#include<onerut_parser/print_chart.hpp>

namespace onerut_parser {

    void print_chart(
            std::shared_ptr<const std::u32string> input,
            const std::vector<std::u32string>& chart) {
        // Check input consistency:
        assert(input);
        for (const auto & chart_line : chart)
            assert(chart_line.size() == input->size());
        // Print:        
        const std::u32string table_horizontal_line(input->size() + 2, U'▓');
        std::cout << unicode_to_utf8(table_horizontal_line) << std::endl;
        std::cout << "▓" << unicode_to_utf8(*input) << "▓" << std::endl;
        std::cout << unicode_to_utf8(table_horizontal_line) << std::endl;
        for (const auto & chart_line : chart)
            std::cout << "▓" << unicode_to_utf8(chart_line) << "▓" << std::endl;
        std::cout << unicode_to_utf8(table_horizontal_line) << std::endl;
    }

}