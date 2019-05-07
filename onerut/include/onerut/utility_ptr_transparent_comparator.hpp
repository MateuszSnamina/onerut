#ifndef ONERUT_UTILITY_PTR_TRANSPARENT_COMPARATOR_HPP
#define ONERUT_UTILITY_PTR_TRANSPARENT_COMPARATOR_HPP

#include<memory>
#include<type_traits>

#include<iostream>//TODO  delete
//namespace onerut {
namespace utility {

    template<class T>
    struct PtrTransparentComparator {
        using is_transparent = void;
        //using is_transparent = void;
        //using bareT = typename std::remove_cv<T>::type;
        using bareT = T;

        // shared_ptr vs shared_ptr:

        bool operator()(const std::shared_ptr<bareT>& lhs, const std::shared_ptr<bareT>& rhs) const {
            return (void*) lhs.get() < (void*) rhs.get();
        }

        bool operator()(const std::shared_ptr<bareT>& lhs, const std::shared_ptr<const bareT>& rhs) const {
            return (void*) lhs.get() < (void*) rhs.get();
        }

        bool operator()(const std::shared_ptr<const bareT>& lhs, const std::shared_ptr<bareT>& rhs) const {
            return (void*) lhs.get() < (void*) rhs.get();
        }

        bool operator()(const std::shared_ptr<const bareT>& lhs, const std::shared_ptr<const bareT>& rhs) const {
            return (void*) lhs.get() < (void*) rhs.get();
        }

        // shared_ptr vs raw_ptr:        

        bool operator()(std::shared_ptr<bareT> lhs, const bareT* rhs) const {
            return  (void*) lhs.get() <  (void*) rhs;
        }

        bool operator()(std::shared_ptr<const bareT> lhs, const bareT* rhs) const {
            return  (void*) lhs.get() <  (void*) rhs;
        }

        // raw_ptr vs shared_ptr:        

        bool operator()(const bareT* lhs, std::shared_ptr<bareT> rhs) const {
            return  (void*) lhs <  (void*) rhs.get();
        }

        bool operator()(const bareT* lhs, std::shared_ptr<const bareT> rhs) const {
            return  (void*) lhs <  (void*) rhs.get();
        }

    };
}
//}

#endif