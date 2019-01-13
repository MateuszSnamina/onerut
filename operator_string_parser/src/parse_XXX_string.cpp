#include<cassert>
#include<cctype>
#include<iostream>
#include<stdexcept>
#include<operator_string_parser/parse_XXX_string.hpp>
#include <c++/5/bits/stl_bvector.h>

namespace {

    operator_string_parser::string_const_span _disregard_one_outer_nesting(
            operator_string_parser::string_const_span span,
            char open = '(', char close = ')') {
        assert(span.first <= span.second);
        assert(operator_string_parser::is_outer_nested(span, open, close));
        return {span.first + 1, span.second - 1};
    }

}

namespace operator_string_parser {

    NestingOpenCloseCharactersMismatchError::NestingOpenCloseCharactersMismatchError(std::string message) :
    std::runtime_error(message) {
    }

    string_const_span lstrip(string_const_span span) {
        assert(span.first <= span.second);
        std::string::const_iterator it;
        for (it = span.first; it != span.second; ++it) {
            if (!std::isspace(*it)) break;
        }
        return {it, span.second};
    }

    string_const_span rstrip(string_const_span span) {
        assert(span.first <= span.second);
        std::string::const_reverse_iterator it;
        for (it = std::string::const_reverse_iterator(span.second); it != std::string::const_reverse_iterator(span.first); ++it) {
            if (!std::isspace(*it)) break;
        }
        return {span.first, it.base()};
    }

    string_const_span lrstrip(string_const_span span) {
        assert(span.first <= span.second);
        return lstrip(rstrip(span));
    }

    bool is_outer_nested(
            string_const_span span,
            char open, char close) {
        assert(span.first <= span.second);
        if (span.first == span.second)
            return false;
        return (*span.first == open && *(span.second - 1) == close);
    }

    string_const_span disregard_one_outer_nesting(
            string_const_span span,
            char open, char close) {
        assert(span.first <= span.second);
        if (is_outer_nested(span, open, close)) {
            return _disregard_one_outer_nesting(span, open, close);
        }
        return span;
    }

    string_const_span disregard_all_outer_nesting(
            string_const_span span,
            char open, char close) {
        assert(span.first <= span.second);
        string_const_span result = span;
        while (is_outer_nested(result, open, close)) {
            result = _disregard_one_outer_nesting(result, open, close);
        }
        return result;
    }

    std::vector<string_const_span> parse_nested_comma_separated_string(
            string_const_span span,
            char sep, char open, char close) {
        assert(span.first <= span.second);
        std::vector<string_const_span> result;
        unsigned nested_level = 0;
        if (span.first == span.second) {
            return result;
        }
        result.push_back(span);
        result.back().first = span.first;
        for (std::string::const_iterator it = span.first; it != span.second; ++it) {
            if (*it == open)
                nested_level++;
            if (*it == close) {
                if (nested_level > 0) {
                    nested_level--;
                } else {
                    const std::string close_char_repr = "'" + std::string(1, close) + "'";
                    const std::string input_string_repr = "\"" + string_span_to_string(span) + "\"";
                    const unsigned pos = it - span.first;
                    const std::string message1 = "Error while parsing " + input_string_repr +
                            " at position " + std::to_string(pos) + ".";
                    const std::string message2 = "To many " + close_char_repr + " chars.";
                    throw NestingOpenCloseCharactersMismatchError(message1 + message2);
                }
            }
            if (nested_level == 0 && *it == sep) {
                result.back().second = it;
                result.emplace_back(it + 1, span.second);
            }
        }
        if (nested_level > 0) {
            const std::string close_char_repr = "'" + std::string(1, close) + "'";
            const std::string input_string_repr = "\"" + string_span_to_string(span) + "\"";
            const unsigned pos = span.second - span.first;
            const std::string message1 = "Error while parsing " + input_string_repr +
                    " at position " + std::to_string(pos) + ".";
            const std::string message2 = "Not enough " + close_char_repr + " chars.";
            throw NestingOpenCloseCharactersMismatchError(message1 + message2);
        }
        return result;
    }

    std::optional<FunctionInfo> try_parse_function(
            string_const_span span) {
        assert(span.first <= span.second);
        std::string::const_iterator it;
        for (it = span.first; it != span.second; ++it) {
            if (!(std::isalnum(*it) || *it == '_'))
                break;
        }
        const string_const_span name_sub_span = {span.first, it};
        const string_const_span argv_sub_span = {it, span.second};        
        if (name_sub_span.first == name_sub_span.second)
            return std::optional<FunctionInfo>();
        if (argv_sub_span.first == argv_sub_span.second) {
            // Treat constant as a function with zero args.
            return std::optional<FunctionInfo>({name_sub_span,
                std::vector<string_const_span>()});
        } else {
            if (!is_outer_nested(argv_sub_span))
                return std::optional<FunctionInfo>();
            try {
                return std::optional<FunctionInfo>({name_sub_span,
                    parse_nested_comma_separated_string(_disregard_one_outer_nesting(argv_sub_span))});
            } catch (NestingOpenCloseCharactersMismatchError&) { // bedzie w przyszlosci mismathc.!!!
                return std::optional<FunctionInfo>();
            }
        }
        assert(false);
        return std::optional<FunctionInfo>(); // this should never happens.        
    }
}