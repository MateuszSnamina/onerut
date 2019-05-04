#ifndef ONERUT_DEPENDENCE_DEPENDENCE_DFS
#define ONERUT_DEPENDENCE_DEPENDENCE_DFS

#include<cassert>
#include<functional>

#include<onerut_dependence/dependence.hpp>

namespace onerut_dependence {

    inline
    void dfs(
            const std::function<void(std::shared_ptr<const Dependable>)> &visit_function,
            const std::function<bool(std::shared_ptr<const Dependable>)> &condition_for_going_deeper,
            std::weak_ptr<const Dependable> dependable) {
        const auto dependable_shared = dependable.lock();
        assert(dependable_shared);
        if (condition_for_going_deeper(dependable_shared)) {
            for (const auto & subdependence : dependable_shared->dependence()) {
                dfs(visit_function, condition_for_going_deeper, subdependence);
            }
        }
        visit_function(dependable_shared);
    }
    /*
        template<class StopT>
        std::vector<std::weak_ptr<const Dependable>>
        dependence_list(const std::function<bool(std::shared_ptr<const Dependable>)> &condition_for_going_deeper) {
            const auto dependable_shared = dependable.lock();
            assert(dependable_shared);
            if (condition_for_going_deeper(dependable_shared)) {
                for (const auto & subdependence : dependable_shared->dependence()) {
                    dfs(visit_function, condition_for_going_deeper, subdependence);
                }
            }
            visit_function(dependable_shared);
        }
     */
}

#endif
