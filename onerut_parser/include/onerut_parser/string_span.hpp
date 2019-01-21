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

    using u32string_const_span = boost::iterator_range<std::u32string::const_iterator>;

    inline std::u32string to_u32string(string_const_span span) {
        return std::u32string(span.begin(), span.end());
    }
    /*
            inline std::string_view to_string_view(string_const_span span) {
                return std::string_view(&*span.begin(), span.end() - span.begin());
            }    
     */
}

#endif 

