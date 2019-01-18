#ifndef OPERATR_STRING_PARSER_TOKEN_HPP
#define OPERATR_STRING_PARSER_TOKEN_HPP

#include<memory>
#include<vector>
#include<optional>
#include<operator_string_parser/string_span.hpp>
#include<string_view>

namespace operator_string_parser {

    //**************************************************************************

    class Token {
    public:
        Token(string_const_span span);
        const string_const_span span;
        virtual std::string str() const = 0;
        virtual ~Token() = default;
    };

    //**************************************************************************

    class LiteralIntToken : public Token {
    public:
        LiteralIntToken(string_const_span span, int value);
        virtual std::string str() const override;
        const int value;
    };

    class LiteralDoubleToken : public Token {
    public:
        LiteralDoubleToken(string_const_span span, double value);
        virtual std::string str() const override;
        const double value;
    };

    class LiteralStringToken : public Token {
    public:
        LiteralStringToken(string_const_span span, std::string value);
        virtual std::string str() const override;
        const std::string value;
    };

    class LiteralExpressionToken : public Token {
    public:
        LiteralExpressionToken(string_const_span span, std::string value);
        virtual std::string str() const override;
        const std::string value;
    };

    class ParanthesisToken : public Token {
    public:

        enum class Type {
            open, close
        };
        ParanthesisToken(string_const_span span, Type type);
        virtual std::string str() const override;
        const Type type;
        // private:
        //    iterator_to_type(std::string::const_iterator it);        
    };

    class SquareBracketToken : public Token {
    public:

        enum class Type {
            open, close
        };
        SquareBracketToken(string_const_span span, Type type);
        virtual std::string str() const override;
        const Type type;
        // private:
        //     iterator_to_type(std::string::const_iterator it);        
    };

    class CurlyBracketToken : public Token {
    public:

        enum class Type {
            open, close
        };
        CurlyBracketToken(string_const_span span, Type type);
        virtual std::string str() const override;
        const Type type;
        //private:
        //   iterator_to_type(std::string::const_iterator it);
    };

    class OperatorToken : public Token {
    public:

        enum class Type {
            plus, minus, prod, div
        };
        OperatorToken(string_const_span span, Type type);
        virtual std::string str() const override;
        const Type type;

    };

    //**************************************************************************

    std::shared_ptr<LiteralIntToken> try_get_int_token(string_const_span span);
    std::shared_ptr<LiteralDoubleToken> try_get_double_token(string_const_span span);
    std::shared_ptr<LiteralStringToken> try_get_string_token(string_const_span span);
    std::shared_ptr<LiteralExpressionToken> try_get_expression_token(string_const_span span);
    std::shared_ptr<ParanthesisToken> try_get_paranthesis_token(string_const_span span);
    std::shared_ptr<SquareBracketToken> try_get_square_bracket_token(string_const_span span);
    std::shared_ptr<CurlyBracketToken> try_get_curly_bracket_token(string_const_span span);
    std::shared_ptr<OperatorToken> try_get_operator_token(string_const_span span);

    //**************************************************************************    

}


#endif