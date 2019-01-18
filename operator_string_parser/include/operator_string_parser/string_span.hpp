#ifndef OPERATR_STRING_PARSER_PARSE_STRING_SPAN_HPP
#define OPERATR_STRING_PARSER_PARSE_STRING_SPAN_HPP

#include<string>
#include<string_view>
#include<boost/range.hpp>

namespace operator_string_parser {

    using string_const_span = boost::iterator_range<std::string::const_iterator>;

    inline std::string string_span_to_string(string_const_span span) {
        return std::string(span.begin(), span.end());
    }

    inline std::string_view make_string_view(string_const_span span) {
        return std::string_view(&*span.begin(), span.end() - span.begin());
    }

}
#endif 

