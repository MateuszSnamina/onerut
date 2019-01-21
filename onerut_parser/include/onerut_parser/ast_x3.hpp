#ifndef ONERUT_PARSER_AST_X3
#define ONERUT_PARSER_AST_X3

#include<string>
#include<vector>

#include<boost/optional.hpp>
#include<boost/spirit/home/x3/support/ast/variant.hpp>
#include<boost/spirit/home/x3/support/ast/position_tagged.hpp>


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

    struct NestedExpression1Info;
    struct NestedExpression2Info;
    struct FunctionInfo;
    // See: https://stackoverflow.com/questions/44949535/parsing-list-of-variants-with-boost-spirit-x3?rq=1

    struct ValueInfo : boost::spirit::x3::variant<
    LitIntInfo,
    LitDoubleInfo,
    IdentifierInfo,
    boost::spirit::x3::forward_ast<FunctionInfo>,
    boost::spirit::x3::forward_ast<NestedExpression1Info>,
    boost::spirit::x3::forward_ast<NestedExpression2Info>
    > {
        ValueInfo() = default;
        ValueInfo(ValueInfo const&) = default;
        ValueInfo& operator=(ValueInfo const&) = default;
        using base_type::base_type;
        using base_type::operator=;
    };

    struct UnaryPlusMinusInfo : boost::spirit::x3::position_tagged {
        boost::optional<char32_t> op;        
        ValueInfo expression;
    };
    
    struct OpGlueInfo : boost::spirit::x3::position_tagged {
        UnaryPlusMinusInfo first_arg;
        boost::optional<UnaryPlusMinusInfo> other_arg;
        OpGlueInfo() = default;
        OpGlueInfo(OpGlueInfo const&) = default;
        OpGlueInfo& operator=(OpGlueInfo const&) = default;

    };

    struct OpArrowInfo : boost::spirit::x3::position_tagged {
        OpGlueInfo first_arg;
        boost::optional<OpGlueInfo> other_arg;
        OpArrowInfo() = default;
        OpArrowInfo(OpArrowInfo const&) = default;
        OpArrowInfo& operator=(OpArrowInfo const&) = default;

    };

    struct OpAtInfo : boost::spirit::x3::position_tagged {
        OpArrowInfo first_arg;
        boost::optional<OpArrowInfo> other_arg;
        OpAtInfo() = default;
        OpAtInfo(OpAtInfo const&) = default;
        OpAtInfo& operator=(OpAtInfo const&) = default;
    };

    struct OpPowInfo : boost::spirit::x3::position_tagged {
        OpAtInfo first_arg;
        boost::optional<OpAtInfo> other_arg;
        OpPowInfo() = default;
        OpPowInfo(OpPowInfo const&) = default;
        OpPowInfo& operator=(OpPowInfo const&) = default;
    };

    struct OpProdDivBitInfo : boost::spirit::x3::position_tagged {
        char32_t op;
        OpPowInfo arg;
    };

    struct OpProdDivInfo : boost::spirit::x3::position_tagged {
        OpPowInfo first_arg;
        std::vector<OpProdDivBitInfo> other_argv;
    };

    struct OpPlusMinusBitInfo : boost::spirit::x3::position_tagged {
        char32_t op;
        OpProdDivInfo arg;
    };

    struct OpPlusMinusInfo : boost::spirit::x3::position_tagged {
        OpProdDivInfo first_arg;
        std::vector<OpPlusMinusBitInfo> other_argv;
    };

    struct ExpressionInfo : boost::spirit::x3::position_tagged {
        OpPlusMinusInfo sum;
    };

    struct FunctionInfo : boost::spirit::x3::position_tagged {
        IdentifierInfo name;
        std::vector<ExpressionInfo> argv;
    };

    struct NestedExpression1Info : boost::spirit::x3::position_tagged {
        ExpressionInfo expression;
    };

    struct NestedExpression2Info : boost::spirit::x3::position_tagged {
        ExpressionInfo expression;
    };

}

#endif