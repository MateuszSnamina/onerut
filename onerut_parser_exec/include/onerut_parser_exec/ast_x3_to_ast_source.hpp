#ifndef ONERUT_PARSER_EXEC_AST_X3_TO_AST_DYN
#define ONERUT_PARSER_EXEC_AST_X3_TO_AST_DYN

#include<onerut_parser_exec/ast_x3.hpp>
#include<onerut_parser_exec/ast_source.hpp>

namespace onerut_parser_exec::onerut_ast {

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::ExpressionInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpAssignInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpPlusMinusInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpProdDivInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpPowInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpAtInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpArrowInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpGlueInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::Value1Info& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::LitDoubleInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::LitPureComplexDoubleInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::LitLongInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpUnaryPlusMinusInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::Value2Info& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::FunctionInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::EmptyFunctionInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);
    
    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::IdentifierInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::NestedExpression1Info& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::NestedExpression2Info& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);

}

#endif