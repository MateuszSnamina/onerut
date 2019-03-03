#ifndef ONERUT_NORMAL_OPERATOR_DOMAIN_SPIN
#define ONERUT_NORMAL_OPERATOR_DOMAIN_SPIN

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    class SpinDomain : public Domain {
    public:
        SpinDomain(uint32_t multiplicity);
        uint32_t size() const override;
        std::string state_name(uint32_t index) const override;        
        const uint32_t multiplicity;
        const uint32_t n_max_stars;
    };

}

#endif