#include<cassert>
#include<cctype>
#include<iostream>
#include<stdexcept>
#include<operator_string_parser/parse_XXX_string.hpp>
#include <c++/5/bits/stl_bvector.h>

namespace {



}

namespace operator_string_parser {

    NestingOpenCloseCharactersMismatchError::NestingOpenCloseCharactersMismatchError(std::string message) :
    std::runtime_error(message) {
    }

    string_const_span lstrip(string_const_span span) {
        assert(span.begin() <= span.end());
        std::string::const_iterator it;
        for (it = span.begin(); it != span.end(); ++it) {
            if (!std::isspace(*it)) break;
        }
        return {it, span.end()};
    }

    string_const_span rstrip(string_const_span span) {
        assert(span.begin() <= span.end());
        std::string::const_reverse_iterator it;
        for (it = std::string::const_reverse_iterator(span.end()); it != std::string::const_reverse_iterator(span.begin()); ++it) {
            if (!std::isspace(*it)) break;
        }
        return {span.begin(), it.base()};
    }

    string_const_span lrstrip(string_const_span span) {
        assert(span.begin() <= span.end());
        return lstrip(rstrip(span));
    }

    bool is_outer_nested(
            string_const_span span,
            char open, char close) {
        assert(span.begin() <= span.end());
        if (span.begin() == span.end())
            return false;
        return (*span.begin() == open && *(span.end() - 1) == close);
    }

    string_const_span _disregard_one_outer_nesting(
            string_const_span span,
            char open, char close) {
        assert(span.begin() <= span.end());
        assert(is_outer_nested(span, open, close));
        return {span.begin() + 1, span.end() - 1};
    }

    string_const_span disregard_one_outer_nesting(
            string_const_span span,
            char open, char close) {
        assert(span.begin() <= span.end());
        if (is_outer_nested(span, open, close)) {
            return _disregard_one_outer_nesting(span, open, close);
        }
        return span;
    }

    string_const_span disregard_all_outer_nesting(
            string_const_span span,
            char open, char close) {
        assert(span.begin() <= span.end());
        string_const_span result = span;
        while (is_outer_nested(result, open, close)) {
            result = _disregard_one_outer_nesting(result, open, close);
        }
        return result;
    }

    std::vector<string_const_span> parse_nested_comma_separated_string(
            string_const_span span,
            char sep, char open, char close) {
        assert(span.begin() <= span.end());
        std::vector<string_const_span> result;
        if (span.begin() == span.end()) {
            return result;
        }
        unsigned nested_level = 0;
        std::string::const_iterator it_start = span.begin();
        for (std::string::const_iterator it = span.begin(); it != span.end(); ++it) {
            if (*it == open)
                nested_level++;
            if (*it == close) {
                if (nested_level > 0) {
                    nested_level--;
                } else {
                    const std::string close_char_repr = "'" + std::string(1, close) + "'";
                    const std::string input_string_repr = "\"" + string_span_to_string(span) + "\"";
                    const unsigned pos = it - span.begin();
                    const std::string message1 =
                            "Error while parsing " + input_string_repr +
                            " at position " + std::to_string(pos) + ".";
                    const std::string message2 = "To many " + close_char_repr + " chars.";
                    throw NestingOpenCloseCharactersMismatchError(message1 + message2);
                }
            }
            if (nested_level == 0 && *it == sep) {
                result.emplace_back(it_start, it);
                it_start = it + 1;
            }
        }
        result.emplace_back(it_start, span.end());
        if (nested_level > 0) {
            const std::string close_char_repr = "'" + std::string(1, close) + "'";
            const std::string input_string_repr = "\"" + string_span_to_string(span) + "\"";
            const unsigned pos = span.end() - span.begin();
            const std::string message1 =
                    "Error while parsing " + input_string_repr +
                    " at position " + std::to_string(pos) + ".";
            const std::string message2 =
                    "Not enough " + close_char_repr + " chars.";
            throw NestingOpenCloseCharactersMismatchError(message1 + message2);
        }
        return result;
    }

    std::optional<FunctionInfo> try_parse_function(
            string_const_span span) {
        assert(span.begin() <= span.end());
        std::string::const_iterator it;
        for (it = span.begin(); it != span.end(); ++it) {
            if (!(std::isalnum(*it) || *it == '_'))
                break;
        }
        const string_const_span name_sub_span = {span.begin(), it};
        const string_const_span argv_sub_span = {it, span.end()};
        if (name_sub_span.begin() == name_sub_span.end())
            return std::optional<FunctionInfo>();
        if (argv_sub_span.begin() == argv_sub_span.end()) {
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

    std::optional<int> try_parse_int(
            string_const_span span) {
        assert(span.begin() <= span.end());
        std::size_t pos;
        try {
            const int result = std::stoi(string_span_to_string(span), &pos);
            if (span.end() == span.begin() + pos)
                return result;
        } catch (std::invalid_argument&) {
            return std::optional<int>();
        }
        return std::optional<int>();
    }

    std::optional<double> try_parse_double(
            string_const_span span) {
        assert(span.begin() <= span.end());
        std::size_t pos;
        try {
            const double result = std::stod(string_span_to_string(span), &pos);
            if (span.end() == span.begin() + pos)
                return result;
        } catch (std::invalid_argument&) {
            return std::optional<double>();
        }
        return std::optional<double>();
    }

    std::optional<std::vector<string_const_span>> try_parse_infix_operator(
            string_const_span span, char op) {
        const auto result = parse_nested_comma_separated_string(span, op);
        if (result.size() > 1)
            return result;
        return std::optional<std::vector < string_const_span >> ();
    }

    std::optional<std::string> try_parse_expression(
            string_const_span span) {
        if (is_outer_nested(span, '[', ']')) {
            span = _disregard_one_outer_nesting(span, '[', ']');
            return string_span_to_string(span);
        }
        return std::optional<std::string>();
    }
}