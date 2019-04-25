#include<sstream>
#include<vector>
#include<boost/algorithm/string/join.hpp>

#include<onerut/aka.hpp>

std::string object_to_aka_string(
        std::shared_ptr<void> object,
        std::multimap<std::shared_ptr<void>, std::string> object_akas) {
    const auto it_lo = object_akas.lower_bound(object);
    const auto it_up = object_akas.upper_bound(object);
    std::vector<std::string> akas;
    for (auto it = it_lo; it != it_up; ++it) {
        const auto& aka = it->second;
        akas.push_back(aka);
    }
    std::ostringstream sstream;
    sstream << "{" << object;
    if (!akas.empty()) {
        sstream << "|" << boost::algorithm::join(akas, "|");
    } else {
        sstream << "|" << ":anonymous:";
    }
    sstream << "}";
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
