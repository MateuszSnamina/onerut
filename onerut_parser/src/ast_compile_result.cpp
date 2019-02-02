#include<onerut_parser/ast_compile_result.hpp>

#include<cassert>
#include<algorithm>

namespace {

    template <typename T>
    std::vector<T> cat(T first, std::vector<T> others) {
        std::vector<T> result;
        result.reserve(others.size());
        result.push_back(first);
        std::copy(cbegin(others), cend(others), back_inserter(result));
        return result;
    }
}

namespace onerut_parser::onerut_ast::compile_result {

    CompileResultNode::CompileResultNode(
            std::shared_ptr<const source::ExpressionNode> expression,
            CompileResult compile_result
            ) :
    expression(expression),
    subexpressions({}),
    compile_result(compile_result) {
    }

    CompileResultNode::CompileResultNode(
            std::shared_ptr<const source::ExpressionNode> expression,
            std::shared_ptr<CompileResultNode> subexpression,
            CompileResult compile_result) :
    expression(expression),
    subexpressions({subexpression}),
    compile_result(compile_result) {
    }

    CompileResultNode::CompileResultNode(
            std::shared_ptr<const source::ExpressionNode> expression,
            std::shared_ptr<CompileResultNode> first_subexpression,
            std::shared_ptr<CompileResultNode> second_subexpression,
            CompileResult compile_result) :
    expression(expression),
    subexpressions({first_subexpression, second_subexpression}),
    compile_result(compile_result) {
    }

    CompileResultNode::CompileResultNode(
            std::shared_ptr<const source::ExpressionNode> expression,
            std::shared_ptr<CompileResultNode> first_subexpression,
            std::vector<std::shared_ptr<CompileResultNode>> others_subexpressions,
            CompileResult compile_result) :
    expression(expression),
    subexpressions(cat(first_subexpression, others_subexpressions)),
    compile_result(compile_result) {
    }

    CompileResultNode::CompileResultNode(
            std::shared_ptr<const source::ExpressionNode> expression,
            std::vector<std::shared_ptr<CompileResultNode>> subexpressions,
            CompileResult compile_result) :
    expression(expression),
    subexpressions(),
    compile_result(compile_result) {
    }

}