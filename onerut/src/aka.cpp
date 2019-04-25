#include<sstream>
#include<boost/algorithm/string/join.hpp>

#include<onerut_normal_operator/eig.hpp>//TODO: try to avoid
//#include<onerut_normal_operator/mean.hpp>//TODO: try to avoid
#include<onerut_convergence_parameter/convergence_parameter.hpp>//TODO: try to avoid

#include<onerut_parser_exec/asset_ref_container.hpp>
#include<onerut/aka.hpp>

std::multimap<std::shared_ptr<void>, std::string> create_object_akas_map() {
    std::multimap<std::shared_ptr<void>, std::string> object_names;
    const auto& identifiers = onerut_parser_exec::AssetRefContainer::global_instance().identifiers();
    for (const auto& identifiers_entry : identifiers) {
        const auto& aka = identifiers_entry.first;
        const auto& asset = identifiers_entry.second;
        assert(asset);
        const auto& asset_deref = asset->get_asset_deref();
        if (asset_deref.is_either_value_or_type()) {
            if (const auto &object = asset_deref.typed_value_or_empty<onerut_normal_operator::Eig>()) {
                //std::cout << aka << " " << *object << "---" << std::endl;
                decltype(object_names)::value_type p(*object, aka);
                object_names.insert(p);
            }
        } else {
            //std::cout << aka << std::endl;
        }
    }
    return object_names;
}

std::string object_to_aka_string(
        std::shared_ptr<void> object,
        std::multimap<std::shared_ptr<void>, std::string> object_akas) {
    const auto it_lo = object_akas.lower_bound(object);
    const auto it_up = object_akas.upper_bound(object);
    std::vector<std::string> names;
    for (auto it = it_lo; it != it_up; ++it) {
        const auto& aka = it->second;
        names.push_back("aka:" + aka);
    }
    std::ostringstream sstream;
    sstream << object;
    if (!names.empty()) {
        sstream << "(" + boost::algorithm::join(names, ", ") + ")";
    }
    return sstream.str();
}

Aka::Aka(std::shared_ptr<void> object,
        std::multimap<std::shared_ptr<void>, std::string> object_akas) :
_object(object),
_object_akas(object_akas) {
}

std::ostream& operator<<(std::ostream& stream, const Aka& aka) {
    stream << object_to_aka_string(aka._object, aka._object_akas);
    return stream;
}
