#include<onerut_parser/ast_asset.hpp>

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

namespace onerut_parser::onerut_ast::asset {

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            Asset asset
            ) :
    source(source),
    subassets({}),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<AssetNode> subasset,
            Asset asset) :
    source(source),
    subassets({subasset}),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<AssetNode> first_subasset,
            std::shared_ptr<AssetNode> second_subasset,
            Asset asset) :
    source(source),
    subassets({first_subasset, second_subasset}),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<AssetNode> first_subasset,
            std::vector<std::shared_ptr<AssetNode>> others_subassets,
            Asset asset) :
    source(source),
    subassets(cat(first_subasset, others_subassets)),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::vector<std::shared_ptr<AssetNode>> subassets,
            Asset asset) :
    source(source),
    subassets(subassets),
    asset(asset) {
    }

}