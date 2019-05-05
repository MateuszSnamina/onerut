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

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

template<class T>
class Presenter;

template<class T>
class PresenterFrame;

template<class T>
std::ostream& operator<<(std::ostream&, const PresenterFrame<T>&);

template<class T>
class PresenterFrame {
public:
    PresenterFrame(
            const Presenter<T>&aka,
            const std::shared_ptr<T>& object);
    const Presenter<T>&_aka;
    const std::shared_ptr<T>& _object;
    friend std::ostream& operator<<<>(std::ostream&, const PresenterFrame<T>&);
};

template<class T>
class Presenter {
public:
    Presenter(
            std::multimap<std::shared_ptr<const void>, std::string> _object_akas,
            std::map<std::shared_ptr<const void>, std::string> object_sources
            );
    std::multimap<std::shared_ptr<const void>, std::string> _object_akas;
    std::map<std::shared_ptr<const void>, std::string> _object_sources;
    PresenterFrame<T> operator()(const std::shared_ptr<T>& object);
};

template<class T>
PresenterFrame<T>::PresenterFrame(
        const Presenter<T>&aka,
        const std::shared_ptr<T>& object) :
_aka(aka),
_object(object) {
}

template<class T>
std::ostream&
operator<<(std::ostream& stream, const PresenterFrame<T>& aka_printer) {
    stream << object_to_aka_string(
            aka_printer._object,
            aka_printer._aka._object_sources,
            aka_printer._aka._object_akas);
    return stream;
}

template<class T>
PresenterFrame<T> Presenter<T>::operator()(const std::shared_ptr<T>& object) {
    return PresenterFrame<T>(*this, object);
}

template<class T>
Presenter<T>::Presenter(
        std::multimap<std::shared_ptr<const void>, std::string> object_akas,
        std::map<std::shared_ptr<const void>, std::string> object_sources) :
_object_akas(object_akas),
_object_sources(object_sources) {
}

#endif