#include<cassert>

#include<onerut_normal_operator/domain_custom.hpp>

namespace onerut_normal_operator {

    CustomDomain::CustomDomain(std::vector<std::string> state_names) :
    _state_names(state_names) {
    }

    unsigned CustomDomain::size() const {
        return _state_names.size();
    }

    std::string CustomDomain::state_name(unsigned index) const {
        assert(index < _state_names.size());
        return _state_names[index];
    }

}