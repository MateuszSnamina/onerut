#ifndef OPERATR_STRING_PARSER_PARSE_XXX_STRING_HPP
#define OPERATR_STRING_PARSER_PARSE_XXX_STRING_HPP

#include<utility>
#include<vector>
#include<string>
#include<optional>
#include<stdexcept>
#include<operator_string_parser/span.hpp>

namespace operator_string_parser {
    
    class NestingOpenCloseCharactersMismatchError : public std::runtime_error {
    public:
        NestingOpenCloseCharactersMismatchError(std::string message);
    };
    
    string_const_span lstrip(string_const_span span);
    string_const_span rstrip(string_const_span span);
    string_const_span lrstrip(string_const_span span);

    bool is_outer_nested(
            string_const_span span,
            char open = '(', char close = ')');

    string_const_span _disregard_one_outer_nesting(
            string_const_span span,
            char open = '(', char close = ')');
    
    string_const_span disregard_one_outer_nesting(
            string_const_span span,
            char open = '(', char close = ')');

    string_const_span disregard_all_outer_nesting(
            string_const_span span,
            char open = '(', char close = ')');
    
    
    std::vector<string_const_span> parse_nested_comma_separated_string(
            string_const_span span,
            char sep = ',', char open = '(', char close = ')');

    struct FunctionInfo {
        string_const_span name;
        std::vector<string_const_span> argv;
    };

    std::optional<FunctionInfo> try_parse_function(
            string_const_span span);
    
    std::optional<int> try_parse_int(
            string_const_span span);
    
    std::optional<double> try_parse_double(
            string_const_span span);
    
    std::optional<std::vector<string_const_span>> try_parse_infix_operator(
            string_const_span span, char op);

    std::optional<std::string> try_parse_expression(
            string_const_span span);
    
}

#endif