#ifndef OPERATR_PARSER_STRING_SPAN_HPP
#define OPERATR_PARSER_STRING_SPAN_HPP

#include<string>
#include<string_view>
#include<boost/range.hpp>

namespace onerut_parser {

    using string_const_span = boost::iterator_range<std::string::const_iterator>;

    inline std::string to_string(string_const_span span) {
        return std::string(span.begin(), span.end());
    }

    inline std::string_view to_string_view(string_const_span span) {
        return std::string_view(&*span.begin(), span.end() - span.begin());
    }

}

#endif 

