#ifndef ONERUT_NORMAL_OPERATOR_DOMAIN_OSCILATOR
#define ONERUT_NORMAL_OPERATOR_DOMAIN_OSCILATOR

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    class OscillatorDomain : public Domain {
    public:
        OscillatorDomain(uint32_t n_max_stars);
        uint32_t size() const override;
        std::string state_name(uint32_t index) const override;
        const uint32_t n_max_stars;
    };

}

#endif
