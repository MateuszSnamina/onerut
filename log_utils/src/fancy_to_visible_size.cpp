#include<sstream>

#include<string_utils/greek_support.hpp>
#include<log_utils/fancy_to_visible_size.hpp>

namespace fancy_logging {

    // -------------------------------------------------------------------------

    ToVisibleSize<std::string>::ToVisibleSize(std::ostream&) {
    }

    unsigned ToVisibleSize<std::string>::size(const std::string& s) const {
        return string_utils::to_greek_number_of_visible_characters_in_result(s);
    }

    // -------------------------------------------------------------------------

    ToVisibleSize<double>::ToVisibleSize(std::ostream& stream) :
    stream(stream) {
    }

    unsigned ToVisibleSize<double>::size(double d) const {
        std::ostringstream sstream;
        sstream.flags(stream.flags());
        sstream.precision(stream.precision());
        sstream << d;
        return sstream.str().size();
    }

}
