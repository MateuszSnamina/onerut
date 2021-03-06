#ifndef ONERUT_AKA_HPP
#define ONERUT_AKA_HPP

#include<string>
#include<map>
#include<memory>
#include<type_traits>
#include<boost/algorithm/string/join.hpp>

#include<string_utils/greek_support.hpp>
#include<onerut/utility_ptr_map.hpp>

namespace {

    template<class Comparator, class T, class U>
    bool is_equal(Comparator&& comparator, T&& lhs, U&& rhs) {
        return !comparator(lhs, rhs) && !comparator(rhs, lhs);
    }

}

// *****************************************************************************
// **************  the core function  ******************************************
// *****************************************************************************

template<class T, class U>
std::string
object_to_aka_string(
        std::shared_ptr<T> object,
        const utility::weak_ptr_map<U, std::string>& object_sources,
        const utility::weak_ptr_multimap<U, std::string>& object_akas) {
    // Find all akas:
    std::vector<std::string> akas;
    {
        const auto it_lo = object_akas.lower_bound(object);
        const auto it_up = object_akas.upper_bound(object);
        for (auto it = it_lo; it != it_up; ++it) {
            const auto& aka = it->second;
            akas.push_back(aka);
        }
    }
    // Concatenate the output string:
    std::ostringstream sstream;
    sstream << "{";
    sstream << object; //DEBUG
    sstream << "|"; //DEBUG
    if (!akas.empty()) {
        sstream << string_utils::StreamToGreek(boost::algorithm::join(akas, "|"));
    } else {
        sstream << ":anonymous:";
    }
    sstream << "|";
    if (object_sources.count(object)) {
        const auto iterator = object_sources.lower_bound(object);
        assert(iterator != object_sources.cend());
        assert(is_equal(utility::PtrTransparentComparator<U>(), (*iterator).first, object));
        const auto source_code = (*iterator).second;
        sstream << "`" << string_utils::StreamToGreek(source_code) << "`";
    } else {
        sstream << ":nosource:";
    }
    sstream << "}";
    // Return:
    return sstream.str();
}

// *****************************************************************************
// *************** Presenter ***************************************************
// *****************************************************************************

template<class U>
class Presenter;

template<class T, class U>
class PresenterFrame;

template<class T, class U>
std::ostream& operator<<(std::ostream&, const PresenterFrame<T, U>&);

template<class T, class U>
class PresenterFrame {
public:
    PresenterFrame(
            const Presenter<U>&aka,
            const std::shared_ptr<T>& object);
    const Presenter<U>&_aka;
    const std::shared_ptr<T>& _object;
    friend std::ostream& operator<<<>(std::ostream&, const PresenterFrame<T, U>&);
};

template<class U>
class Presenter {
public:
    Presenter(
            utility::weak_ptr_multimap<U, std::string> object_akas,
            utility::weak_ptr_map<U, std::string> object_sources
            );
    utility::weak_ptr_multimap<U, std::string> _object_akas;
    utility::weak_ptr_map<U, std::string> _object_sources;
    template<class T>
    PresenterFrame<T, U> operator()(const std::shared_ptr<T>& object) const;
};

template<class U>
Presenter<U>
make_presenter(
        utility::weak_ptr_multimap<U, std::string> object_akas,
        utility::weak_ptr_map<U, std::string> object_sources
        );

// *****************************************************************************
// **************  Presenter -- templates implementation  **********************
// *****************************************************************************

template<class T, class U>
PresenterFrame<T, U>::PresenterFrame(
        const Presenter<U>&aka,
        const std::shared_ptr<T>& object) :
_aka(aka),
_object(object) {
}

template<class T, class U>
std::ostream&
operator<<(std::ostream& stream, const PresenterFrame<T, U>& aka_printer) {
    stream << object_to_aka_string(
            aka_printer._object,
            aka_printer._aka._object_sources,
            aka_printer._aka._object_akas);
    return stream;
}

template<class U>
template<class T>
PresenterFrame<T, U>
Presenter<U>::operator()(const std::shared_ptr<T>& object) const {
    return PresenterFrame<T, U>(*this, object);
}

template<class U>
Presenter<U>::Presenter(
        utility::weak_ptr_multimap<U, std::string> object_akas,
        utility::weak_ptr_map<U, std::string> object_sources) :
_object_akas(object_akas),
_object_sources(object_sources) {
}

template<class U>
Presenter<U>
make_presenter(
        utility::weak_ptr_multimap<U, std::string> object_akas,
        utility::weak_ptr_map<U, std::string> object_sources
        ) {
    return Presenter<U>(object_akas, object_sources);
}

#endif