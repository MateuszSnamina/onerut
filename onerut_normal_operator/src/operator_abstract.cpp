#include<cassert>

#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // --------------  Domain  -------------------------------------------------
    // -------------------------------------------------------------------------

    Domain::Domain(std::vector<std::string> state_names) :
    state_names(state_names) {
    }

    unsigned Domain::size() const {
        return state_names.size();
    }

    std::unique_ptr<StateIndex> Domain::crate_state(unsigned index) const {
        return std::unique_ptr<StateIndex>(new StateIndex{index, shared_from_this()});
    }

    std::string Domain::to_str() const {
        std::string result;
        for (unsigned index = 0; index < state_names.size(); ++index)
            result += "【#" + std::to_string(index) + "»" + state_names[index] + "】";
        return result;
    }

    bool
    are_the_same_domains(const Domain& domain1, const Domain& domain2) {
        return std::addressof(domain1) == std::addressof(domain2);
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
        return domain->state_names.at(index);
    }

    std::string StateIndex::to_str() const {
        std::string result;
        result = "【#" + std::to_string(index) + "»" + fetch_name() + "】";
        return result;
    }

}