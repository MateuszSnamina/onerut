#ifndef ONERUT_NORMAL_OPERATOR_DOMAIN_EG
#define ONERUT_NORMAL_OPERATOR_DOMAIN_EG

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    class EgDomain : public Domain {
    public:
        EgDomain();
        uint32_t size() const override;
        std::string state_name(uint32_t index) const override;        
    };

}

#endif