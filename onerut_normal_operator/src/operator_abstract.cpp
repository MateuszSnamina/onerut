#include<cassert>
#include<algorithm>

#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ----------------  Helper functions  -------------------------------------
    // -------------------------------------------------------------------------    

    bool are_the_same_domains(
            const std::shared_ptr<const AbstractOperator>& first_operator,
            const std::vector<std::shared_ptr<const AbstractOperator> >& other_operators) {
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        return std::all_of(begin(other_operators), end(other_operators),
                [&first_operator](const AbstractOpPtrT & other_operator) {
                    return are_the_same_domains(*first_operator->get_domain(), *other_operator->get_domain());
                });
    }

    bool are_the_same_domains(
            const std::vector<std::shared_ptr<const AbstractOperator> >& operators) {
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        return std::adjacent_find(
                operators.begin(), operators.end(),
                [](const AbstractOpPtrT & lhs_operator, const AbstractOpPtrT & rhs_operator) {
                    return !are_the_same_domains(*lhs_operator->get_domain(), *rhs_operator->get_domain());
                }) == operators.end();
    }

}