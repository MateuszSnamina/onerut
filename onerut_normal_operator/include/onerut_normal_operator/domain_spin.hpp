#ifndef ONERUT_NORMAL_DOMAIN_SPIN
#define ONERUT_NORMAL_DOMAIN_SPIN

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    class SpinDomain : public Domain {
    public:
        SpinDomain(unsigned multiplicity);
        unsigned size() const override;
        std::string state_name(unsigned index) const override;        
        const unsigned multiplicity;
        const unsigned n_max_stars;
    };

}

#endif
