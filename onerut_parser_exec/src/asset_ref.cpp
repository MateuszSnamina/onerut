#include<onerut_parser_exec/asset_ref.hpp>

namespace onerut_parser_exec {

    //------------------

    AssetConstRef::AssetConstRef(std::string name, AssetDeref value) :
    name(name),
    value(value) {
    }

    std::string AssetConstRef::get_name() const {
        return name;
    }

    AssetDeref AssetConstRef::get_asset_deref() const {
        return value;
    }

    //------------------------------------

    AssetNotConstRef::AssetNotConstRef(std::string name, AssetDeref value) :
    name(name),
    value(value) {
    }

    std::string AssetNotConstRef::get_name() const {
        return name;
    }

    AssetDeref AssetNotConstRef::get_asset_deref() const {
        return value;
    }

    void AssetNotConstRef::set_asset(AssetDeref new_value) {
        value = new_value;
    }

    //------------------

    AssetUnsetRef::AssetUnsetRef(std::string name) :
    name(name) {
    }

    std::string AssetUnsetRef::get_name() const {
        return name;
    }

    AssetDeref AssetUnsetRef::get_asset_deref() const {
        return AssetDeref();
    }

}
