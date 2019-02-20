#ifndef ONERUT_PARSER_ASSET_REF_CONTAINER
#define ONERUT_PARSER_ASSET_REF_CONTAINER

#include<optional>
#include<string>
#include<map>
#include<onerut_parser/asset_ref.hpp>

namespace onerut_parser {

    class AssetRefContainer {
    public:
        static AssetRefContainer& global_instance();
        std::optional<std::shared_ptr<AbstractAssetRef>> get_or_empty(const std::string& name) const;
        bool put(const std::string& name, std::shared_ptr<AbstractAssetRef> ref);  //TODO: delete name from a signature, read name from ref object through its std::string get_name() const method
        void force_put(const std::string& name, std::shared_ptr<AbstractAssetRef> ref);  //TODO: delete name from a signature, read name from ref object through its std::string get_name() const method
    private:
        std::map<std::string, std::shared_ptr<AbstractAssetRef>> identifiers;
    };

}

#endif
