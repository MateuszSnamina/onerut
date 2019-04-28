#include<cassert>

#include<onerut_normal_operator/domain_eg.hpp>

namespace onerut_normal_operator {

    EgDomain::EgDomain() {
    }

    uint32_t EgDomain::size() const {
        return 2;
    }

    std::string EgDomain::state_name(uint32_t index) const {
        assert(index < size());
        switch (index) {
            case 0:
                return "zeta";
            case 1:
                return "xi";
            default:
                return "internal_error";
        }
    }

}