#include<cassert>
#include<algorithm>

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // --------------  Domain  -------------------------------------------------
    // -------------------------------------------------------------------------

    inline
    std::vector<std::string> Domain::state_names() const {
        std::vector<std::string> result;
        for (unsigned index = 0; index < size(); ++index) {
            result.push_back(state_name(index));
        }
        return result;
    }

    std::unique_ptr<StateIndex> Domain::crate_state(unsigned index) const {
        return std::unique_ptr<StateIndex>(new StateIndex{index, shared_from_this()});
    }

    // -------------------------------------------------------------------------
    // ----------------  StateIndex  -------------------------------------------
    // -------------------------------------------------------------------------

    StateIndex::StateIndex(unsigned index, std::shared_ptr<const Domain> domain) :
    domain(domain),
    index(index) {
        assert(index <= domain->size());
    }

    std::string StateIndex::fetch_name() const {
        return domain->state_name(index);
    }

    std::string StateIndex::to_str() const {
        std::string result;
        result = "【#" + std::to_string(index) + "»" + fetch_name() + "】";
        return result;
    }

    // -------------------------------------------------------------------------
    // ----------------  Helper functions  -------------------------------------
    // -------------------------------------------------------------------------    

    bool
    are_the_same_domains(const Domain& first_domain, const Domain& second_domain) {
        return std::addressof(first_domain) == std::addressof(second_domain);
    }

    bool
    are_the_same_domains(const Domain& first_domain, const std::vector<Domain>& other_domains) {
        return std::all_of(begin(other_domains), end(other_domains),
                [&first_domain](const Domain & other_domain) {
                    return are_the_same_domains(first_domain, other_domain);
                });
    }

    bool
    are_the_same_domains(const std::vector<Domain>& domains) {
        return std::adjacent_find(
                domains.begin(), domains.end(),
                [](const Domain& lhs_domain, const Domain & rhs_domain) {
                    return !are_the_same_domains(lhs_domain, rhs_domain);
                }) == domains.end();
    }


}