#ifndef ONERUT_PARSER_AST_COMPILE_RESULT
#define ONERUT_PARSER_AST_COMPILE_RESULT

#include<string>
#include<vector>
#include<memory>

#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/ast_source.hpp>

//TO DO IN ANOTHER HPP:


namespace onerut_parser::onerut_ast::asset {

    class AssetNode {
    public:
        AssetNode(
                std::shared_ptr<const source::SourceNode> source,
                Asset asset
                );
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
        // -----------------------
        LinesStyledChartInfo to_ast_chart() const;
        ErrorsChartInfo to_errors_chart() const;
        // -----Internal data: ---
        const std::shared_ptr<const source::SourceNode> source;
        const std::vector<std::shared_ptr<AssetNode>> subassets;//TODO change_to_subassets!!
        const Asset asset;
    private:
        void to_ast_chart(
                unsigned deepness,
                LinesStyledChartInfo& ast_chart) const;
        void to_errors_chart(
                ErrorsChartInfo& erros_chart) const;        
    };

}

#endif
