#ifndef ONERUT_AKA_HPP
#define ONERUT_AKA_HPP

#include<string>
#include<map>
#include<memory>

#include<onerut_parser_exec/asset_ref_container.hpp>

template<class T>
std::multimap<std::shared_ptr<const void>, std::string>
create_object_akas_map() {
    std::multimap<std::shared_ptr<const void>, std::string> object_akas;
    const auto& identifiers = onerut_parser_exec::AssetRefContainer::global_instance().identifiers();
    for (const auto& identifiers_entry : identifiers) {
        const auto& aka = identifiers_entry.first;
        const auto& asset = identifiers_entry.second;
        assert(asset);
        const auto& asset_deref = asset->get_asset_deref();
        if (asset_deref.is_either_value_or_type()) {
            if (const auto &object = asset_deref.typed_value_or_empty<T>()) {
                decltype(object_akas)::value_type p(*object, aka);
                object_akas.insert(p);
            }
        }
    }
    return object_akas;
}

std::string
object_to_aka_string(
        std::shared_ptr<const void> object,
        std::map<std::shared_ptr<const void>, std::string> object_sources,
        std::multimap<std::shared_ptr<const void>, std::string> object_akas);

class Aka {
public:
    Aka(std::shared_ptr<const void> object,
            std::multimap<std::shared_ptr<const void>, std::string> object_akas,
            std::map<std::shared_ptr<const void>, std::string> object_sources);
private:
    std::shared_ptr<const void> _object;
    std::multimap<std::shared_ptr<const void>, std::string> _object_akas;
    std::map<std::shared_ptr<const void>, std::string> _object_sources;
    friend std::ostream& operator<<(std::ostream&, const Aka&);
};

#endif

