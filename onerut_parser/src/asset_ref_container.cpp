#include<onerut_parser/asset_ref_container.hpp>

namespace onerut_parser {

    // #########################################################################
    // #################### GLOBAL DATABASE ####################################
    // #########################################################################

    AssetRefContainer& AssetRefContainer::global_instance() {
        static AssetRefContainer _instance;
        return _instance;
    }

    std::optional<std::shared_ptr<AbstractAssetRef>>
    AssetRefContainer::get_or_empty(const std::string& name) const {
        try {
            return identifiers.at(name);
        } catch (std::out_of_range&) {
            return std::optional<std::shared_ptr < AbstractAssetRef >> ();
        }//TODO change to count,
    }

    bool
    AssetRefContainer::put(const std::string& name, std::shared_ptr<AbstractAssetRef> ref) {
        if (identifiers.count(name))
            return false;
        identifiers[name] = ref;
        return true;
    }

    void
    AssetRefContainer::force_put(const std::string& name, std::shared_ptr<AbstractAssetRef> ref) {
        identifiers[name] = ref;
    }

}