#include<onerut_parser_exec/vector_cat.hpp>
#include<onerut_parser_exec/ast_asset.hpp>

#include<cassert>
#include<algorithm>

namespace onerut_parser_exec::onerut_ast::asset {

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            Asset asset
            ) :
    source(source),
    subnodes({}),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<AssetNode> subasset,
            Asset asset) :
    source(source),
    subnodes({subasset}),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<AssetNode> first_subasset,
            std::shared_ptr<AssetNode> second_subasset,
            Asset asset) :
    source(source),
    subnodes({first_subasset, second_subasset}),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<AssetNode> first_subasset,
            std::vector<std::shared_ptr<AssetNode>> others_subassets,
            Asset asset) :
    source(source),
    subnodes(cat(first_subasset, others_subassets)),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::vector<std::shared_ptr<AssetNode>> subassets,
            Asset asset) :
    source(source),
    subnodes(subassets),
    asset(asset) {
    }

}