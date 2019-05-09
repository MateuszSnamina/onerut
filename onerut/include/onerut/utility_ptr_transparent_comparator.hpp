#ifndef ONERUT_UTILITY_PTR_TRANSPARENT_COMPARATOR_HPP
#define ONERUT_UTILITY_PTR_TRANSPARENT_COMPARATOR_HPP

#include<memory>
#include<type_traits>

//namespace onerut {
namespace utility {

    template<class T>
    struct PtrTransparentComparator {
        using is_transparent = void;

        // ---------------------------------------------------------------------
        using bareT = typename std::remove_cv<T>::type;

        // --------  shared_ptr vs shared_ptr  ---------------------------------

        bool operator()(
                const std::shared_ptr<bareT>& lhs,
                const std::shared_ptr<bareT>& rhs) const {
            return lhs.get() < rhs.get();
        }

        bool operator()(
                const std::shared_ptr<bareT>& lhs,
                const std::shared_ptr<const bareT>& rhs) const {
            return lhs.get() < rhs.get();
        }

        bool operator()(
                const std::shared_ptr<const bareT>& lhs,
                const std::shared_ptr<bareT>& rhs) const {
            return lhs.get() < rhs.get();
        }

        bool operator()(
                const std::shared_ptr<const bareT>& lhs,
                const std::shared_ptr<const bareT>& rhs) const {
            return lhs.get() < rhs.get();
        }

        // --------  weak_ptr vs shared_ptr  ---------------------------------

        bool operator()(
                const std::weak_ptr<bareT>& lhs,
                const std::shared_ptr<bareT>& rhs) const {
            assert(!lhs.expired());
            return lhs.lock().get() < rhs.get();
        }

        bool operator()(
                const std::weak_ptr<bareT>& lhs,
                const std::shared_ptr<const bareT>& rhs) const {
            assert(!lhs.expired());
            return lhs.lock().get() < rhs.get();
        }

        bool operator()(
                const std::weak_ptr<const bareT>& lhs,
                const std::shared_ptr<bareT>& rhs) const {
            assert(!lhs.expired());
            return lhs.lock().get() < rhs.get();
        }

        bool operator()(
                const std::weak_ptr<const bareT>& lhs,
                const std::shared_ptr<const bareT>& rhs) const {
            assert(!lhs.expired());
            return lhs.lock().get() < rhs.get();
        }

        // --------  shared_ptr vs weak_ptr  ---------------------------------

        bool operator()(
                const std::shared_ptr<bareT>& lhs,
                const std::weak_ptr<bareT>& rhs) const {
            assert(!rhs.expired());
            return lhs.get() < rhs.lock().get();
        }

        bool operator()(
                const std::shared_ptr<bareT>& lhs,
                const std::weak_ptr<const bareT>& rhs) const {
            assert(!rhs.expired());
            return lhs.get() < rhs.lock().get();
        }

        bool operator()(
                const std::shared_ptr<const bareT>& lhs,
                const std::weak_ptr<bareT>& rhs) const {
            assert(!rhs.expired());
            return lhs.get() < rhs.lock().get();
        }

        bool operator()(
                const std::shared_ptr<const bareT>& lhs,
                const std::weak_ptr<const bareT>& rhs) const {
            assert(!rhs.expired());
            return lhs.get() < rhs.lock().get();
        }

        // --------  shared_ptr vs raw_ptr  ------------------------------------

        bool operator()(
                const std::shared_ptr<bareT> & lhs,
                const bareT* rhs) const {
            return lhs.get() < rhs;
        }

        bool operator()(
                const std::shared_ptr<const bareT> & lhs,
                const bareT* rhs) const {
            return lhs.get() < rhs;
        }

        // --------  raw_ptr vs shared_ptr  ------------------------------------

        bool operator()(
                const bareT* lhs,
                const std::shared_ptr<bareT> & rhs) const {
            return lhs < rhs.get();
        }

        bool operator()(
                const bareT* lhs,
                const std::shared_ptr<const bareT> & rhs) const {
            return lhs < rhs.get();
        }

        // --------  weak_ptr vs raw_ptr  --------------------------------------

        bool operator()(
                const std::weak_ptr<bareT> & lhs,
                const bareT* rhs) const {

            return lhs.lock().get() < rhs;
        }

        bool operator()(
                const std::weak_ptr<const bareT> & lhs,
                const bareT* rhs) const {
            assert(!lhs.expired());
            return lhs.lock().get() < rhs;
        }

        // --------  raw_ptr vs weak_ptr ---------------------------------------

        bool operator()(
                const bareT* lhs,
                const std::weak_ptr<bareT> & rhs) const {
            assert(!rhs.expired());
            return lhs < rhs.lock().get();
        }

        bool operator()(
                const bareT* lhs,
                const std::weak_ptr<const bareT> & rhs) const {
            assert(!rhs.expired());
            return lhs < rhs.lock().get();
        }
    };
}
//}

#endif