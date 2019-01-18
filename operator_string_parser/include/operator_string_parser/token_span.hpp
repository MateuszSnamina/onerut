#ifndef OPERATR_STRING_PARSER_PARSE_TOKEN_SPAN_HPP
#define OPERATR_STRING_PARSER_PARSE_TOKEN_SPAN_HPP

#include<vector>
#include<operator_string_parser/node.hpp>
#include<boost/utility.hpp>
#include <boost/range/iterator_range_core.hpp>
#include<memory>
namespace operator_string_parser {

    //using tokens_const_span = std::pair<, std::string::const_iterator>;
    using TokensConstSpan = boost::iterator_range<std::vector<std::shared_ptr<Token>::const_iterator>>;
    //inline std::string tokens_span_to_string(tokens_const_span span) {

    //return std::string(span.first, span.second);

    //"║"
    //}
}
#endif 

