#ifndef ONERUT_PARSER_PRINT_CHART
#define ONERUT_PARSER_PRINT_CHART

#include<memory>
#include<string>
#include<vector>

namespace onerut_parser {
    
    void print_chart(
            std::shared_ptr<const std::u32string> input,
            const std::vector<std::u32string>& chart);

}

#endif