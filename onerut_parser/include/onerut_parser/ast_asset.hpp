#ifndef ONERUT_PARSER_AST_COMPILE_RESULT
#define ONERUT_PARSER_AST_COMPILE_RESULT

#include<string>
#include<vector>
#include<memory>

#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/ast_source.hpp>

namespace onerut_parser::onerut_ast::asset {

    class AssetNode {
    public:
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                Asset asset
                );
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                std::shared_ptr<AssetNode> subsource,
                Asset asset);
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                std::shared_ptr<AssetNode> first_subsource,
                std::shared_ptr<AssetNode> second_subsource,
                Asset asset);
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                std::shared_ptr<AssetNode> first_subsource,
                std::vector<std::shared_ptr<AssetNode>> others_subsources,
                Asset asset);
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                std::vector<std::shared_ptr<AssetNode>> subsources,
                Asset asset);
        virtual ~AssetNode() = default;
        // To-chart functions:
        LinesStyledChartInfo to_chart() const;
        // Internal data:
        const std::shared_ptr<const source::SourceNode> source;
        const std::vector<std::shared_ptr<AssetNode>> subsources;
        const Asset asset;
    private:
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const;

    };

}

#endif
