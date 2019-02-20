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
    subsources({}),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<AssetNode> subsource,
            Asset asset) :
    source(source),
    subsources({subsource}),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<AssetNode> first_subsource,
            std::shared_ptr<AssetNode> second_subsource,
            Asset asset) :
    source(source),
    subsources({first_subsource, second_subsource}),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::shared_ptr<AssetNode> first_subsource,
            std::vector<std::shared_ptr<AssetNode>> others_subsources,
            Asset asset) :
    source(source),
    subsources(cat(first_subsource, others_subsources)),
    asset(asset) {
    }

    AssetNode::AssetNode(
            std::shared_ptr<const source::SourceNode> source,
            std::vector<std::shared_ptr<AssetNode>> subsources,
            Asset asset) :
    source(source),
    subsources(subsources),
    asset(asset) {
    }

}