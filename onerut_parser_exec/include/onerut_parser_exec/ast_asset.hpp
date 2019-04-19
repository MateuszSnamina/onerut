#ifndef ONERUT_PARSER_EXEC_AST_COMPILE_RESULT
#define ONERUT_PARSER_EXEC_AST_COMPILE_RESULT

#include<string>
#include<vector>
#include<memory>
#include<functional>

#include<onerut_parser_exec/print_chart.hpp>
#include<onerut_parser_exec/ast_source.hpp>

namespace onerut_parser_exec::onerut_ast::asset {

    class AssetNode {
    public:
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                Asset asset);
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                std::shared_ptr<AssetNode> subasset,
                Asset asset);
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                std::shared_ptr<AssetNode> first_subasset,
                std::shared_ptr<AssetNode> second_subasset,
                Asset asset);
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                std::shared_ptr<AssetNode> first_subasset,
                std::vector<std::shared_ptr<AssetNode>> others_subassets,
                Asset asset);
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                std::vector<std::shared_ptr<AssetNode>> subassets,
                Asset asset);
        virtual ~AssetNode() = default;
        // ----------------------------------------
        LinesChartInfo to_ast_chart(
                std::function<esc::EscData(const Asset&)> asset_to_esc_data) const;
        ErrorsChartInfo to_errors_chart() const;
        // -----Internal data: --------------------
        const std::shared_ptr<const source::SourceNode> source;
        const std::vector<std::shared_ptr<AssetNode>> subassets;
        const Asset asset;
    private:
        void to_ast_chart(
                unsigned deepness,
                LinesChartInfo& ast_chart,
                std::function<esc::EscData(const Asset&)> asset_to_esc_data) const;
        void to_errors_chart(
                ErrorsChartInfo& erros_chart) const;
    };

}

#endif
