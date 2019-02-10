#ifndef STRING_UTILS_GREEK_SUPPORT_HPP
#define STRING_UTILS_GREEK_SUPPORT_HPP

#include<string>
#include<string_view>

namespace string_utils {
    std::string to_greek(std::string str);
    std::string to_greek(std::string_view str_view);

    int to_greek_delta_in_number_of_visible_characters(std::string_view str_view);
    unsigned to_greek_number_of_visible_characters_in_result(std::string_view str_view);

}

#endif
