#ifndef ONERUT_AKA_HPP
#define ONERUT_AKA_HPP

#include<string>
#include<map>
#include<memory>
#include<boost/algorithm/string/join.hpp>

#include<string_utils/greek_support.hpp>

// *****************************************************************************
// **************  the core function  ******************************************
// *****************************************************************************

template<class T>
std::string
object_to_aka_string(
        std::shared_ptr<const T> object,
        std::map<std::shared_ptr<const T>, std::string> object_sources,
        std::multimap<std::shared_ptr<const T>, std::string> object_akas) {
    // Find all akas:
    const auto it_lo = object_akas.lower_bound(object);
    const auto it_up = object_akas.upper_bound(object);
    std::vector<std::string> akas;
    for (auto it = it_lo; it != it_up; ++it) {
        const auto& aka = it->second;
        akas.push_back(aka);
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
        sstream << "`" << string_utils::StreamToGreek(object_sources[object]) << "`";
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
            std::multimap<std::shared_ptr<const T>, std::string> _object_akas,
            std::map<std::shared_ptr<const T>, std::string> object_sources
            );
    std::multimap<std::shared_ptr<const T>, std::string> _object_akas;
    std::map<std::shared_ptr<const T>, std::string> _object_sources;
    PresenterFrame<T> operator()(const std::shared_ptr<T>& object) const;
};

// *****************************************************************************
// **************  Presenter -- templates implementation  **********************
// *****************************************************************************

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
PresenterFrame<T> Presenter<T>::operator()(const std::shared_ptr<T>& object) const {
    return PresenterFrame<T>(*this, object);
}

template<class T>
Presenter<T>::Presenter(
        std::multimap<std::shared_ptr<const T>, std::string> object_akas,
        std::map<std::shared_ptr<const T>, std::string> object_sources) :
_object_akas(object_akas),
_object_sources(object_sources) {
}

#endif