#ifndef ONERUT_GRAMMA_PARSER
#define ONERUT_GRAMMA_PARSER

#include<string>

namespace onerut_parser {
    bool parse(const std::u32string& input);
    bool parse(const std::string input);    
}

#endif