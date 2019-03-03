#ifndef ONERUT_NORMAL_OPERATOR_DOMAIN_CUSTOM
#define ONERUT_NORMAL_OPERATOR_DOMAIN_CUSTOM

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // --------------  Domain  -------------------------------------------------
    // -------------------------------------------------------------------------

    class CustomDomain : public Domain {
    public:
        CustomDomain(std::vector<std::string> state_names);
        unsigned size() const override;
        std::string state_name(unsigned index) const override;
    public:
        const std::vector<std::string> _state_names;
    };

}

#endif