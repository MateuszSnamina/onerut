#ifndef ONERUT_PARSER_UNICODE_SUPPORT
#define ONERUT_PARSER_UNICODE_SUPPORT

#include<string>
#include<string_view>

namespace string_utils {

    std::string unicode_to_utf8(const std::u32string & uni);
    std::string unicode_to_utf8(const std::u32string_view& uni);
    std::u32string unicode_from_utf8(const std::string & str);
    std::u32string unicode_from_utf8(const std::string_view& str);

}
#endif