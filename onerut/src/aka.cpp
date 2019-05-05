#include<sstream>
#include<vector>
#include<boost/algorithm/string/join.hpp>

#include<string_utils/greek_support.hpp>
#include<onerut/aka.hpp>

std::string
object_to_aka_string(
        std::shared_ptr<const void> object,
        std::map<std::shared_ptr<const void>, std::string> object_sources,
        std::multimap<std::shared_ptr<const void>, std::string> object_akas) {
    const auto it_lo = object_akas.lower_bound(object);
    const auto it_up = object_akas.upper_bound(object);
    std::vector<std::string> akas;
    for (auto it = it_lo; it != it_up; ++it) {
        const auto& aka = it->second;
        akas.push_back(aka);
    }
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
    return sstream.str();
}

Aka::Aka(std::shared_ptr<const void> object,
        std::multimap<std::shared_ptr<const void>, std::string> object_akas,
        std::map<std::shared_ptr<const void>, std::string> object_sources) :
_object(object),
_object_akas(object_akas),
_object_sources(object_sources) {
}

std::ostream& operator<<(std::ostream& stream, const Aka& aka) {
    stream << object_to_aka_string(aka._object, aka._object_sources, aka._object_akas);
    return stream;
}
