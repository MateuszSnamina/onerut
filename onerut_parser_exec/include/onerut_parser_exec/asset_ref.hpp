#ifndef ONERUT_PARSER_ASSET_REF
#define ONERUT_PARSER_ASSET_REF

#include<onerut_parser_exec/asset_deref.hpp>

namespace onerut_parser {

    class AbstractAssetRef {
    public:
        virtual AssetDeref get_asset_deref() const = 0;
        virtual std::string get_name() const = 0;
        virtual ~AbstractAssetRef() = default;
    };

    class AssetConstRef : public AbstractAssetRef {
    public:
        AssetConstRef(std::string name, AssetDeref value);
        AssetDeref get_asset_deref() const override;
        std::string get_name() const override;
    private:
        const std::string name;
        const AssetDeref value;
    };

    class AssetNotConstRef : public AbstractAssetRef {
    public:
        AssetNotConstRef(std::string name, AssetDeref value);
        AssetDeref get_asset_deref() const override;
        std::string get_name() const override;
        void set_asset(AssetDeref new_value);
    private:
        const std::string name;
        AssetDeref value;
    };

    class AssetUnsetRef : public AbstractAssetRef {
    public:
        AssetUnsetRef(std::string name);
        AssetDeref get_asset_deref() const override;
        std::string get_name() const override;
    private:
        const std::string name;
    };

}

#endif
