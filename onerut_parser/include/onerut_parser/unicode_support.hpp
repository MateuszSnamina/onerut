#ifndef ONERUT_PARSER_UNICODE_SUPPORT
#define ONERUT_PARSER_UNICODE_SUPPORT

#include <string>

std::string unicode_to_utf8(const std::u32string & uni);
std::u32string unicode_from_utf8(const std::string & str);

#endif