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
    unique_dependence_list(
            std::function<bool(std::shared_ptr<const Dependable>) > condition_for_break,
            std::weak_ptr<const Dependable> head) {
        std::vector<std::weak_ptr<const Dependable>> result;
        const auto adder = [&result](std::weak_ptr<const Dependable> dependable) {
            bool is_already_added = std::find_if(
                    cbegin(result), cend(result),
                    [&dependable](std::weak_ptr<const Dependable> dependable_in_reslt) -> bool {
                        return dependable.lock() == dependable_in_reslt.lock();
                    }
            ) != cend(result);
            if (!is_already_added) {
                result.push_back(dependable);
            }
        };
        dfs(adder, condition_for_break, head);
        assert(result.back().lock() == head.lock());
        result.pop_back();
        return result;
    }

}

#endif
