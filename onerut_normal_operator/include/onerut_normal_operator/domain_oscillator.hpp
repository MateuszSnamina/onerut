#ifndef ONERUT_NORMAL_DOMAIN_OSCILATOR
#define ONERUT_NORMAL_DOMAIN_OSCILATOR

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    class OscillatorDomain : public Domain {
    public:
        OscillatorDomain(unsigned n_max_stars);
        unsigned size() const override;
        std::string state_name(unsigned index) const override;
        const unsigned n_max_stars;
    };

}

#endif
