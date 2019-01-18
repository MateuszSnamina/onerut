#ifndef ONERUT_AST_X3
#define ONERUT_AST_X3

#include<string>
#include<vector>

#include<boost/spirit/home/x3.hpp> ///????
#include<boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include<boost/spirit/home/x3/support/ast/variant.hpp>

//zrobic namespace ast_x3
namespace ast {

    struct IdentifierInfo : boost::spirit::x3::position_tagged {
        char first_char;
        std::vector<char> other_chars;
        //std::string str() const;
    };

    struct LitIntInfo : boost::spirit::x3::position_tagged {
        int value;
        // std::string str() const;
    };

    struct LitDoubleInfo : boost::spirit::x3::position_tagged {
        double value;
        //  std::string str() const;
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

    // std::string to_string(const ExpressionInfo& i);
    /*
        struct expression_printer {
            typedef std::string result_type;
            result_type operator()(const IdentifierInfo & i) const;
            result_type operator()(const LitIntInfo & i) const;
            result_type operator()(const LitDoubleInfo & i) const;
            result_type operator()(const FunctionInfo & i) const;
        };
     */
}

#endif