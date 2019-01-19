#include<codecvt>
#include<locale>
#include<onerut_parser/unicode_support.hpp>

std::string unicode_to_utf8(const std::u32string& uni) {
    std::wstring_convert < std::codecvt_utf8<char32_t>, char32_t > convert;
    return convert.to_bytes(uni);
}

std::u32string unicode_from_utf8(const std::string& str) {
    std::wstring_convert < std::codecvt_utf8<char32_t>, char32_t > convert;
    return convert.from_bytes(str);
}