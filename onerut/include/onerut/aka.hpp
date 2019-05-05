#ifndef ONERUT_AKA_HPP
#define ONERUT_AKA_HPP


#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<memory>
#include<boost/algorithm/string/join.hpp>

#include<string_utils/greek_support.hpp>

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

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

//TODO: object with snippet do another header:

template<class T>
struct ObjectWithSnippet {
    const std::shared_ptr<T> object;
    const std::string code_snippet;
};

template<class T>
std::string
object_to_aka_string_ver2(
        const ObjectWithSnippet<T>& object_with_snippet,
        std::multimap<std::shared_ptr<const void>, std::string> object_akas) {
    const auto it_lo = object_akas.lower_bound(object_with_snippet.object);
    const auto it_up = object_akas.upper_bound(object_with_snippet.object);
    std::vector<std::string> akas;
    for (auto it = it_lo; it != it_up; ++it) {
        const auto& aka = it->second;
        akas.push_back(aka);
    }
    std::ostringstream sstream;
    sstream << "{";
    sstream << object_with_snippet.object; //DEBUG
    sstream << "|"; //DEBUG
    if (!akas.empty()) {
        sstream << string_utils::StreamToGreek(boost::algorithm::join(akas, "|"));
    } else {
        sstream << ":anonymous:";
    }
    sstream << "|";
    sstream << "`" << string_utils::StreamToGreek(object_with_snippet.code_snippet) << "`";
    sstream << "}";
    return sstream.str();
}

template<class T>
class Aka_ver2;

template<class T>
std::ostream& operator<<(std::ostream&, const Aka_ver2<T>&);

template<class T>
class Aka_ver2 {
public:
    Aka_ver2(
            const ObjectWithSnippet<T>& object_with_snippet,
            const std::multimap<std::shared_ptr<const void>, std::string> & object_akas);
private:
    const ObjectWithSnippet<T>& _object_with_snippet;
    const std::multimap<std::shared_ptr<const void>, std::string> & _object_akas;
    friend std::ostream& operator<<<>(std::ostream&, const Aka_ver2<T>&);
};

template<class T>
Aka_ver2<T>::Aka_ver2(
        const ObjectWithSnippet<T>& object_with_snippet,
        const std::multimap<std::shared_ptr<const void>, std::string> & object_akas) :
_object_with_snippet(object_with_snippet),
_object_akas(object_akas) {
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const Aka_ver2<T>& aka) {
    stream << object_to_aka_string(aka._object_with_snippet, aka._object_akas);
    return stream;
}

#endif