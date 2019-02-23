#ifndef LOG_UTILS_FANCY_TO_VISIBLE_SIZE
#define LOG_UTILS_FANCY_TO_VISIBLE_SIZE


#include<string>

namespace fancy_logging {

    template<typename T>
    struct ToVisibleSize;

    template<>
    struct ToVisibleSize<std::string> {
        ToVisibleSize(std::ostream& stream);
        unsigned size(const std::string& s) const;
    };

    template<>
    struct ToVisibleSize<double> {
        ToVisibleSize(std::ostream& stream);
        unsigned size(double d) const;
        std::ostream& stream;
    };

}

#endif