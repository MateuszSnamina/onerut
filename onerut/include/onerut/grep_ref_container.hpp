#ifndef ONERUT_GREP_REF_CONTAINER_HPP
#define ONERUT_GREP_REF_CONTAINER_HPP

#include<string>
#include<map>
#include<memory>

#include<onerut_parser_exec/asset_ref_container.hpp>
#include<onerut/utility_ptr_map.hpp>

/*
 * The function scans onerut_parser_exec::AssetRefContainer::global_instance()
 * in search for references for assets holding value of type T.
 */

template<class T>
utility::weak_ptr_multimap<T, std::string>
grep_ref_container() {
    utility::weak_ptr_multimap<T, std::string> object_akas;
    const auto& identifiers = onerut_parser_exec::AssetRefContainer::global_instance().identifiers();
    for (const auto& identifiers_entry : identifiers) {
        const auto& aka = identifiers_entry.first;
        const auto& asset = identifiers_entry.second;
        assert(asset);
        assert(aka == asset->get_name());
        const auto& asset_deref = asset->get_asset_deref();
        if (asset_deref.is_either_value_or_type()) {
            if (const auto &object = asset_deref.typed_value_or_empty<T>()) {
                typename utility::weak_ptr_multimap<T, std::string>::value_type p(*object, aka);
                object_akas.insert(p);
            }
        }
    }
    return object_akas;
}

#endif