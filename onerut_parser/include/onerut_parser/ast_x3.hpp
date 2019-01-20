#ifndef ONERUT_PARSER_AST_X3
#define ONERUT_PARSER_AST_X3

#include<string>
#include<vector>

#include<boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include<boost/spirit/home/x3/support/ast/variant.hpp>

namespace onerut_parser::onerut_ast::x3 {

    struct LitDoubleInfo : boost::spirit::x3::position_tagged {
        double value;
    };

    struct LitIntInfo : boost::spirit::x3::position_tagged {
        int value;
    };

    struct IdentifierInfo : boost::spirit::x3::position_tagged {
        char32_t first_char;
        std::vector<char32_t> other_chars;
        std::u32string name() const;
    };

    struct NestedExpressionInfo;
    struct FunctionInfo;

    // See: https://stackoverflow.com/questions/44949535/parsing-list-of-variants-with-boost-spirit-x3?rq=1

    struct ValueInfo : boost::spirit::x3::variant<
    LitIntInfo,
    LitDoubleInfo,
    IdentifierInfo,
    boost::spirit::x3::forward_ast<FunctionInfo>,
    boost::spirit::x3::forward_ast<NestedExpressionInfo>
    > {
        ValueInfo() = default;
        ValueInfo(ValueInfo const&) = default;
        ValueInfo& operator=(ValueInfo const&) = default;
        using base_type::base_type;
        using base_type::operator=;
    };

    struct OpProdInfo : boost::spirit::x3::position_tagged {
        std::vector<ValueInfo> argv;
    };

    struct OpPlusInfo : boost::spirit::x3::position_tagged {
        std::vector<OpProdInfo> argv;
    };

    struct ExpressionInfo : boost::spirit::x3::position_tagged {
        OpPlusInfo sum;
    };

    struct FunctionInfo : boost::spirit::x3::position_tagged {
        IdentifierInfo name;
        std::vector<ExpressionInfo> argv;
    };

    struct NestedExpressionInfo : boost::spirit::x3::position_tagged {
        ExpressionInfo expression;
    };



}

#endif