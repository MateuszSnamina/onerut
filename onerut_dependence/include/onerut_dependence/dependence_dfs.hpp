#ifndef ONERUT_DEPENDENCE_DEPENDENCE_DFS
#define ONERUT_DEPENDENCE_DEPENDENCE_DFS

#include<cassert>
#include<functional>
//#include<iostream> // TODO delete: debug

#include<onerut_dependence/dependence.hpp>

namespace onerut_dependence {

    //TODO move to CPP

    inline
    void dfs(
            const std::function<void(std::shared_ptr<const Dependable>)> &visit_function,
            const std::function<bool(std::shared_ptr<const Dependable>)> &condition_for_break,
            std::weak_ptr<const Dependable> head) {
        const auto dependable_shared = head.lock();
        assert(dependable_shared);
        for (const auto & subdependence : dependable_shared->dependence()) {
            assert(subdependence.lock());
            if (!condition_for_break(subdependence.lock())) {
                dfs(visit_function, condition_for_break, subdependence);
            }
        }
        visit_function(dependable_shared);
    }

    std::vector<std::weak_ptr<const Dependable>>
    dependence_list(
            std::function<bool(std::shared_ptr<const Dependable>) > condition_for_break,
            std::weak_ptr<const Dependable> head) {
        std::vector<std::weak_ptr<const Dependable>> result;
        const auto adder = [&result](std::weak_ptr<const Dependable> dependable) {
            result.push_back(dependable);
        };
        dfs(adder, condition_for_break, head);
        return result;
    }

}

#endif
