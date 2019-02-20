#ifndef ONERUT_PARSER_IDENTIFIER
#define ONERUT_PARSER_IDENTIFIER

#include<onerut_parser/asset_deref.hpp>

namespace onerut_parser {

    class AbstractAssetRef {
    public:
        virtual AssetDeref get_asset_deref() const = 0;
        virtual ~AbstractAssetRef() = default;
    };

    class AssetConstRef : public AbstractAssetRef {
    public:
        AssetConstRef(std::string name, AssetDeref value);
        AssetDeref get_asset_deref() const override;
        std::string get_name() const;
    private:
        const std::string name;
        const AssetDeref value;
    };

    class AssetNotConstRef : public AbstractAssetRef {
    public:
        AssetNotConstRef(std::string name, AssetDeref value);
        AssetDeref get_asset_deref() const override;
        void set_asset(AssetDeref new_value);
        std::string get_name() const;
    private:
        const std::string name;
        AssetDeref value;
    };

    class AssetUnsetRef : public AbstractAssetRef {
    public:
        AssetUnsetRef(std::string name);
        AssetDeref get_asset_deref() const override;
        std::string get_name() const;
    private:
        const std::string name;
    };

}

#endif
