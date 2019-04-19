#ifndef ONERUT_PARSER_EXEC_ASSET
#define ONERUT_PARSER_EXEC_ASSET

#include<cassert>
#include<memory>
#include<variant>
#include<optional>
#include<any>
#include<stdexcept>

#include<onerut_parser_exec/asset_error.hpp>
#include<onerut_parser_exec/asset_deref.hpp>
#include<onerut_parser_exec/asset_ref.hpp>

namespace onerut_parser_exec {

    class Asset {
    public:
        // Construction:
        Asset() = default;
        Asset(const Asset&) = default;
        Asset(Asset&&) = default;
        Asset & operator=(const Asset&) = default;
        Asset & operator=(Asset&&) = default;
        static Asset from_reference(std::shared_ptr<AbstractAssetRef> reference);
        static Asset from_deref_asset(AssetDeref deref_asset);
        template<typename T> static Asset from_type();
        template<typename T> static Asset from_value(std::shared_ptr<T> value);
        static Asset from_compile_error(std::shared_ptr<CompileError> error);
        bool is_reference() const;
        std::optional<std::shared_ptr<AbstractAssetRef>> reference_or_empty() const;
        std::optional<AssetDeref> deref_asset_or_empty() const;
        AssetDeref deref() const;
        // TODO: _or_throw member functions.
    private:
        using VariantType = std::variant<
                std::shared_ptr<AbstractAssetRef>,
                AssetDeref>;
        VariantType _content;
        // We use the tag 'from_content' to mope up the overload issues:
        // Asset(VariantType) vs Asset(Asset&)
        struct FromContentT;
        static const FromContentT from_content;
        Asset(const VariantType content, FromContentT);
    };

    struct Asset::FromContentT {
    };

    // *************************************************************************
    // ********   TEMPLATES IMPLEMENTATION   ***********************************
    // *************************************************************************

    template<typename T>
    Asset Asset::from_type() {
        AssetDeref deref_asset = AssetDeref::from_type<T>();
        return from_deref_asset(deref_asset);
    }

    template<typename T>
    Asset Asset::from_value(std::shared_ptr<T> value) {
        AssetDeref deref_asset = AssetDeref::from_value(value);
        return from_deref_asset(deref_asset);
    }
}
#endif
