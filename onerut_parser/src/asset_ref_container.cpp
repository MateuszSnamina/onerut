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
        if (identifiers.count(name) == 1) {
            return identifiers.at(name);
        } else {
            return std::optional<std::shared_ptr < AbstractAssetRef >> ();
        }
    }

    bool
    AssetRefContainer::put(std::shared_ptr<AbstractAssetRef> ref) {
        if (identifiers.count(ref->get_name()))
            return false;
        identifiers[ref->get_name()] = ref;
        return true;
    }

    void
    AssetRefContainer::force_put(std::shared_ptr<AbstractAssetRef> ref) {
        identifiers[ref->get_name()] = ref;
    }

    void AssetRefContainer::clear(){
        identifiers.clear();
    }
}