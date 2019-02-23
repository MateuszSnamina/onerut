#ifndef LOG_UTILS_FANCY_VISIBLE_SIZE_COMPARATOR
#define LOG_UTILS_FANCY_VISIBLE_SIZE_COMPARATOR

#include<log_utils/fancy_to_visible_size.hpp>

namespace fancy_logging {

    template<class T>
    struct VisibleLengthComparator {
        VisibleLengthComparator(std::ostream& stream);
        bool compare(const T& lhs, const T& rhs);
        const ToVisibleSize<T> to_string_size;
    };

    template<class T>
    VisibleLengthComparator<T>::VisibleLengthComparator(std::ostream& stream) :
    to_string_size(stream) {
    }

    template<class T>
    bool VisibleLengthComparator<T>::compare(const T& lhs, const T& rhs) {
        return to_string_size.size(lhs) < to_string_size.size(rhs);
    }

}

#endif
