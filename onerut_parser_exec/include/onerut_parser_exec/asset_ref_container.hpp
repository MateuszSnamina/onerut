#ifndef ONERUT_PARSER_EXEC_ASSET_REF_CONTAINER
#define ONERUT_PARSER_EXEC_ASSET_REF_CONTAINER

#include<optional>
#include<string>
#include<map>
#include<onerut_parser_exec/asset_ref.hpp>

namespace onerut_parser_exec {

    class AssetRefContainer {
    public:
        static AssetRefContainer& global_instance();
        std::optional<std::shared_ptr<AbstractAssetRef>> get_or_empty(const std::string& name) const;
        bool put(std::shared_ptr<AbstractAssetRef> ref);
        void force_put(std::shared_ptr<AbstractAssetRef> ref);
        void clear();
        const std::map<std::string, std::shared_ptr<AbstractAssetRef>>& identifiers() const;
    private:
        std::map<std::string, std::shared_ptr<AbstractAssetRef>> _identifiers;
    };

}

#endif
