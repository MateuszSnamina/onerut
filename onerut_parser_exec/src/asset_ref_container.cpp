#include<onerut_parser_exec/asset_ref_container.hpp>

namespace onerut_parser_exec {

    // #########################################################################
    // #################### GLOBAL DATABASE ####################################
    // #########################################################################

    AssetRefContainer& AssetRefContainer::global_instance() {
        static AssetRefContainer instance;
        return instance;
    }

    std::optional<std::shared_ptr<AbstractAssetRef>>
    AssetRefContainer::get_or_empty(const std::string& name) const {
        if (_identifiers.count(name) == 1) {
            return _identifiers.at(name);
        } else {
            return std::optional<std::shared_ptr < AbstractAssetRef >> ();
        }
    }

    bool
    AssetRefContainer::put(std::shared_ptr<AbstractAssetRef> ref) {
        if (_identifiers.count(ref->get_name()))
            return false;
        _identifiers[ref->get_name()] = ref;
        return true;
    }

    void
    AssetRefContainer::force_put(std::shared_ptr<AbstractAssetRef> ref) {
        _identifiers[ref->get_name()] = ref;
    }

    void
    AssetRefContainer::clear() {
        _identifiers.clear();
    }

    const std::map<std::string, std::shared_ptr<AbstractAssetRef>>&
    AssetRefContainer::identifiers() const {
        return _identifiers;
    }
    
}