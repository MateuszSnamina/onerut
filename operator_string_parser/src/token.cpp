#include<cassert>
#include<memory>
#include<map>
#include<operator_string_parser/token.hpp>
#include<operator_string_parser/parse_XXX_string.hpp>

#include<iostream>
#include<regex>

#include<boost/convert.hpp>
#include<boost/convert/lexical_cast.hpp>

//using boost::convert;
//using boost::lexical_cast;

struct boost::cnv::by_default : public boost::cnv::lexical_cast {
};




namespace operator_string_parser {

    //**************************************************************************

    Token::Token(string_const_span span) :
    span(span) {
        assert(span.begin() <= span.end());
    }

    LiteralIntToken::LiteralIntToken(string_const_span span, int value) :
    Token(span),
    value(value) {
    }

    std::string LiteralIntToken::str() const {
        return "I:" + std::to_string(value);
    }

    LiteralDoubleToken::LiteralDoubleToken(string_const_span span, double value) :
    Token(span),
    value(value) {
    }

    std::string LiteralDoubleToken::str() const {
        return "D:" + std::to_string(value);
    }

    LiteralStringToken::LiteralStringToken(string_const_span span, std::string value) :
    Token(span),
    value(value) {
    }

    std::string LiteralStringToken::str() const {
        return "S:" + value;
    }

    LiteralExpressionToken::LiteralExpressionToken(string_const_span span, std::string value) :
    Token(span),
    value(value) {
    }

    std::string LiteralExpressionToken::str() const {
        return "E:" + value;
    }

    ParanthesisToken::ParanthesisToken(string_const_span span, ParanthesisToken::Type type) :
    Token(span),
    type(type) {
    }

    std::string ParanthesisToken::str() const {
        const std::map<Type, std::string> value_str_map = {
            {Type::open, "("},
            {Type::close, ")"}
        };
        return value_str_map.at(type);

    }

    SquareBracketToken::SquareBracketToken(string_const_span span, Type type) :
    Token(span),
    type(type) {

    }

    std::string SquareBracketToken::str() const {
        const std::map<Type, std::string> value_str_map = {
            {Type::open, "["},
            {Type::close, "]"}
        };
        return value_str_map.at(type);
    }

    CurlyBracketToken::CurlyBracketToken(string_const_span span, Type type) :
    Token(span),
    type(type) {

    }

    std::string CurlyBracketToken::str() const {
        const std::map<Type, std::string> value_str_map = {
            {Type::open, "{"},
            {Type::close, "}"}
        };
        return value_str_map.at(type);
    }

    OperatorToken::OperatorToken(string_const_span span, Type type) :
    Token(span),
    type(type) {
    }

    std::string OperatorToken::str() const {
        std::string result;
        switch (type) {
            case Type::plus: result = "+";
            case Type::minus: result = "-";
            case Type::prod: result = "*";
            case Type::div: result = "/";
            default: result = "IllegalOperator";
                assert(false);
        };
        return result;
    }

    //**************************************************************************    

    std::shared_ptr<LiteralIntToken> try_get_int_token(string_const_span span) {
        assert(span.begin() <= span.end());
        std::shared_ptr<LiteralIntToken> result;
        const std::regex integer_token_pattern(R"(^[+-]?\d+)");
        std::smatch m;
        if (std::regex_search(span.begin(), span.end(), m, integer_token_pattern)) {
            const auto global_sumbatch = m[0];
            const boost::iterator_range<std::string::const_iterator> token_span = {global_sumbatch.first, global_sumbatch.second};
            const auto value = boost::convert<int>(token_span);
            result = std::make_shared<LiteralIntToken>(token_span, *value);
        }
        return result;
    }

    /*
    std::shared_ptr<LiteralIntToken> try_get_int_token(string_const_span span) {
        // Maximum munch version.
        assert(span.begin() <= span.end());
        std::shared_ptr<LiteralIntToken> result;
        if (span.begin() == span.end())
            return result;
        for (std::string::const_iterator it = span.begin() + 1; it != span.end() + 1; ++it) {
            if (const auto value = try_parse_int({span.begin(), it})) {
                const string_const_span token_span = {span.begin(), it};
                result = std::make_shared<LiteralIntToken>(token_span, *value);
            } else {
                const char first_character = *span.begin();
                const bool first_character_amnesty = (it == span.begin() + 1) &&
                (first_character == '-' || first_character == '+');
                if (!first_character_amnesty)
                    break;
            }
        }
        return result;
    }
     */

    std::shared_ptr<LiteralDoubleToken> try_get_double_token(string_const_span span) {
        assert(span.begin() <= span.end());
        std::shared_ptr<LiteralDoubleToken> result;
        const std::regex double_token_pattern(R"(^[+-]?(?:(?:\d+\.\d*)|(?:\d*\.\d+)|(?:\d+))(?:e[+-]?\d+)?)");
        std::smatch m;
        if (std::regex_search(span.begin(), span.end(), m, double_token_pattern)) {
            const auto global_sumbatch = m[0];
            const boost::iterator_range<std::string::const_iterator> token_span = {global_sumbatch.first, global_sumbatch.second};
            const auto value = boost::convert<double>(token_span);
            result = std::make_shared<LiteralDoubleToken>(token_span, *value);
        }
        return result;
    }

    std::shared_ptr<LiteralStringToken> try_get_string_token(string_const_span span) {
        assert(span.begin() <= span.end());
        std::shared_ptr<LiteralStringToken> result;
        const std::regex string_token_pattern(R"xxx(^"((?:(?:\\")|(?:[^"]))*)")xxx");
        std::smatch m;
        if (std::regex_search(span.begin(), span.end(), m, string_token_pattern)) {
            //std::cout << "dopasowane:" << m.str() << std::endl;            
            const auto global_sumbatch = m[0];
            const boost::iterator_range<std::string::const_iterator> token_span = {global_sumbatch.first, global_sumbatch.second};
            const auto value = m[1].str();
            result = std::make_shared<LiteralStringToken>(token_span, value);
        }
        return result;
    }


    /*
     void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}
     */

    /*
           std::shared_ptr<LiteralExpressionToken> try_get_expression_token(string_const_span span) {

            }

           std::shared_ptr<ParanthesisToken> try_get_paranthesis_token(string_const_span span) {

            }

           std::shared_ptr<SquareBracketToken> try_get_square_bracket_token(string_const_span span) {

            }

           std::shared_ptr<CurlyBracketToken> try_get_curly_bracket_token(string_const_span span) {

            }

         std::shared_ptr<OperatorToken> try_get_operator_token(string_const_span span) {

            }

     */

    //**************************************************************************    

}