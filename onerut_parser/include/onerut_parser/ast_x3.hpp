#ifndef ONERUT_PARSER_AST_X3
#define ONERUT_PARSER_AST_X3

#include<string>
#include<vector>

#include<boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include<boost/spirit/home/x3/support/ast/variant.hpp>

namespace onerut_parser::onerut_ast::x3 {

    struct IdentifierInfo : boost::spirit::x3::position_tagged {
        char32_t first_char;
        std::vector<char32_t> other_chars;
    };

    struct LitIntInfo : boost::spirit::x3::position_tagged {
        int value;
    };

    struct LitDoubleInfo : boost::spirit::x3::position_tagged {
        double value;
    };

    struct FunctionInfo;

    struct ExpressionInfo : boost::spirit::x3::variant<
    LitIntInfo,
    LitDoubleInfo,
    IdentifierInfo,
    boost::spirit::x3::forward_ast<FunctionInfo>
    > {
        //ExpressionInfo() = default;
        //ExpressionInfo(ExpressionInfo const&) = default;
        //ExpressionInfo& operator=(ExpressionInfo const&) = default;
        using base_type::base_type;
        using base_type::operator=;
    };

    struct FunctionInfo : boost::spirit::x3::position_tagged {
        IdentifierInfo name;
        std::vector<ExpressionInfo> argv;
    };

}

#endif