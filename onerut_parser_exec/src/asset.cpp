#include<onerut_parser_exec/common_visitors.hpp>
#include<onerut_parser_exec/asset.hpp>

namespace onerut_parser_exec {

    // *************************************************************************
    // ********************** HELPER FUNCTIONS   *******************************
    // *************************************************************************

    namespace {

        struct DereferenceVisitor {
            AssetDeref operator()(const std::shared_ptr < AbstractAssetRef>& reference) const;
            AssetDeref operator()(const AssetDeref& results) const;
        };

        AssetDeref
        DereferenceVisitor::operator()(const std::shared_ptr < AbstractAssetRef>& reference) const {
            return reference->get_asset_deref();
        }

        AssetDeref
        DereferenceVisitor::operator()(const AssetDeref& results) const {
            return results;
        }

    }

    // *************************************************************************
    // ********************** COMPILE RESULT ***********************************
    // *************************************************************************    

    Asset::Asset(const VariantType content, FromContentT) :
    _content(content) {
    }

    Asset Asset::from_reference(std::shared_ptr<AbstractAssetRef> reference) {
        Asset::VariantType content{
            std::in_place_type<std::shared_ptr < AbstractAssetRef>>,
            reference};
        return Asset(content, from_content);
    }

    Asset
    Asset::from_deref_asset(AssetDeref deref_asset) {
        Asset::VariantType content{
            std::in_place_type<AssetDeref>,
            deref_asset};
        return Asset(content, from_content);
    }

    Asset
    Asset::from_compile_error(std::shared_ptr<CompileError> error) {
        AssetDeref deref_asset = AssetDeref::from_compile_error(error);
        return from_deref_asset(deref_asset);
    }

    bool
    Asset::is_reference() const {
        const IsContentVisitor<std::shared_ptr < AbstractAssetRef>> is_empty_visitor;
        return std::visit(is_empty_visitor, _content);
    }

    std::optional<std::shared_ptr<AbstractAssetRef>>
    Asset::reference_or_empty() const {
        const ContentOrEmptyVisitor<std::shared_ptr < AbstractAssetRef>> reference_or_empty_visitor;
        return std::visit(reference_or_empty_visitor, _content);
    }

    std::optional<AssetDeref>
    Asset::deref_asset_or_empty() const {
        const ContentOrEmptyVisitor<AssetDeref> deref_asset_or_empty_visitor;
        return std::visit(deref_asset_or_empty_visitor, _content);
    }

    AssetDeref
    Asset::deref() const {
        const DereferenceVisitor deref_visitor;
        return std::visit(deref_visitor, _content);

    }

}