#ifndef ONERUT_UTILITY_PTR_MAP_HPP
#define ONERUT_UTILITY_PTR_MAP_HPP

#include<memory>
#include<onerut/utility_ptr_transparent_comparator.hpp>

namespace utility {

    template<class T, class U>
    using weak_ptr_map =
    std::map<std::weak_ptr<T>, U, utility::PtrTransparentComparator<T> >;

    template<class T, class U>
    using weak_ptr_multimap =
    std::multimap<std::weak_ptr<T>, U, utility::PtrTransparentComparator<T> >;

    template<class T, class U>
    using shared_ptr_map =
    std::map<std::shared_ptr<T>, U, utility::PtrTransparentComparator<T> >;

    template<class T, class U>
    using shared_ptr_multimap =
    std::multimap<std::shared_ptr<T>, U, utility::PtrTransparentComparator<T> >;

}

#endif 