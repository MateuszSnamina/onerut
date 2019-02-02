#ifndef ONERUT_PARSER_AST_COMPILE_RESULT
#define ONERUT_PARSER_AST_COMPILE_RESULT

#include<string>
#include<vector>
#include<memory>

#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/ast_source.hpp>

namespace onerut_parser::onerut_ast::compile_result {

    class CompileResultNode {
    public:
        CompileResultNode(
                std::shared_ptr<const source::SourceNode> source,
                CompileResult compile_result
                );
        CompileResultNode(
                std::shared_ptr<const source::SourceNode> source,
                std::shared_ptr<CompileResultNode> subsource,
                CompileResult compile_result);
        CompileResultNode(
                std::shared_ptr<const source::SourceNode> source,
                std::shared_ptr<CompileResultNode> first_subsource,
                std::shared_ptr<CompileResultNode> second_subsource,
                CompileResult compile_result);
        CompileResultNode(
                std::shared_ptr<const source::SourceNode> source,
                std::shared_ptr<CompileResultNode> first_subsource,
                std::vector<std::shared_ptr<CompileResultNode>> others_subsources,
                CompileResult compile_result);
        CompileResultNode(
                std::shared_ptr<const source::SourceNode> source,
                std::vector<std::shared_ptr<CompileResultNode>> subsources,
                CompileResult compile_result);
        virtual ~CompileResultNode() = default;
        // To-chart functions:
        LinesStyledChartInfo to_chart() const;
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const;
        // Internal data:
        const std::shared_ptr<const source::SourceNode> source;
        const std::vector<std::shared_ptr<CompileResultNode>> subsources;
        const CompileResult compile_result;
    };

}

#endif
