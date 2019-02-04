#include<codecvt>
#include<locale>
#include<string_utils/unicode_support.hpp>

std::string unicode_to_utf8(const std::u32string& uni) {
    std::wstring_convert < std::codecvt_utf8<char32_t>, char32_t > convert;
    return convert.to_bytes(uni);
}

std::string unicode_to_utf8(const std::u32string_view& uni) {
    std::wstring_convert < std::codecvt_utf8<char32_t>, char32_t > convert;
    return convert.to_bytes(uni.cbegin(), uni.cend());
}

std::u32string unicode_from_utf8(const std::string& str) {
    std::wstring_convert < std::codecvt_utf8<char32_t>, char32_t > convert;
    return convert.from_bytes(str);
}

std::u32string unicode_from_utf8(const std::string_view& str) {
    std::wstring_convert < std::codecvt_utf8<char32_t>, char32_t > convert;
    return convert.from_bytes(str.cbegin(), str.cend());
}
