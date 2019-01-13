#ifndef OPERATR_STRING_PARSER_PARSE_SPAN_HPP
#define OPERATR_STRING_PARSER_PARSE_SPAN_HPP

#include<string>

namespace operator_string_parser {

    using string_const_span = std::pair<std::string::const_iterator, std::string::const_iterator>;

    inline std::string string_span_to_string(string_const_span span) {
        return std::string(span.first, span.second);
    }
}
#endif 

