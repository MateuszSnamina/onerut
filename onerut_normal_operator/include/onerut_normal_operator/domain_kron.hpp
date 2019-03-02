#ifndef ONERUT_NORMAL_DOMAIN_KRON
#define ONERUT_NORMAL_DOMAIN_KRON

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    class KronDomain : public Domain {
    public:
        KronDomain(std::vector<std::shared_ptr<const Domain> > domains);
        unsigned size() const override;
        std::string state_name(unsigned index) const override;
        std::vector<std::shared_ptr<const Domain> > domains;
        const std::vector<unsigned> domain_sizes;
        const std::vector<unsigned> weights;
    };

    class SiteIndex { //TODO change into placeholder
    public:
        SiteIndex(std::shared_ptr<const KronDomain> domain, unsigned index); //TODO private
        unsigned index;
        std::shared_ptr<const KronDomain> domain;
    };

}

#endif
