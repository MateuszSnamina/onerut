#ifndef STRING_UTILS_STRING_SPAN_HPP
#define STRING_UTILS_STRING_SPAN_HPP

#include<cassert>
#include<string>
#include<string_view>
#include<boost/range.hpp>

namespace onerut_parser_exec {//TODO new namespace

    using string_const_span = boost::iterator_range<std::string::const_iterator>;

    inline std::string to_string(string_const_span span) {
        return std::string(span.begin(), span.end());
    }

    inline std::string_view to_string_view(string_const_span span) {
        return std::string_view(&*span.begin(), span.end() - span.begin());
    }

    inline std::string_view to_string_view(std::string::const_iterator it1, std::string::const_iterator it2) {
        assert(it1 <= it2);
        string_const_span span{it1, it2};
        return to_string_view(span);
    }

    // -------------------------------------------------------------------------

    using u32string_const_span = boost::iterator_range<std::u32string::const_iterator>;

    inline std::u32string to_u32string(u32string_const_span span) {
        return std::u32string(span.begin(), span.end());
    }

    inline std::u32string_view to_u32string_view(u32string_const_span span) {
        return std::u32string_view(&*span.begin(), span.end() - span.begin());
    }

    inline std::u32string_view to_u32string_view(std::u32string::const_iterator it1, std::u32string::const_iterator it2) {
        assert(it1 <= it2);
        u32string_const_span span{it1, it2};
        return to_u32string_view(span);
    }
}

#endif 

