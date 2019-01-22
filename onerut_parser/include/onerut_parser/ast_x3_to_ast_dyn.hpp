#ifndef ONERUT_PARSER_AST_X3_TO_AST_DYN
#define ONERUT_PARSER_AST_X3_TO_AST_DYN

#include<onerut_parser/ast_x3.hpp>
#include<onerut_parser/ast_dyn.hpp>

namespace onerut_parser::onerut_ast {

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::ExpressionInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpPlusMinusInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpProdDivInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpPowInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpAtInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpArrowInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpGlueInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::Value1Info& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::LitDoubleInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::LitIntInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpUnaryPlusMinusInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::Value2Info& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::FunctionInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::IdentifierInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::NestedExpression1Info& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::NestedExpression2Info& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

}

#endif