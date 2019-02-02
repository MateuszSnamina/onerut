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
            std::shared_ptr<const source::SourceNode> source,
            CompileResult compile_result
            ) :
    source(source),
    subsources({}),
    compile_result(compile_result) {
    }

    CompileResultNode::CompileResultNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<CompileResultNode> subsource,
            CompileResult compile_result) :
    source(source),
    subsources({subsource}),
    compile_result(compile_result) {
    }

    CompileResultNode::CompileResultNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<CompileResultNode> first_subsource,
            std::shared_ptr<CompileResultNode> second_subsource,
            CompileResult compile_result) :
    source(source),
    subsources({first_subsource, second_subsource}),
    compile_result(compile_result) {
    }

    CompileResultNode::CompileResultNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<CompileResultNode> first_subsource,
            std::vector<std::shared_ptr<CompileResultNode>> others_subsources,
            CompileResult compile_result) :
    source(source),
    subsources(cat(first_subsource, others_subsources)),
    compile_result(compile_result) {
    }

    CompileResultNode::CompileResultNode(
            std::shared_ptr<const source::SourceNode> source,
            std::vector<std::shared_ptr<CompileResultNode>> subsources,
            CompileResult compile_result) :
    source(source),
    subsources({}),
    compile_result(compile_result) {
    }

}