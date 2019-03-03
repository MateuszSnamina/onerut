#ifndef ONERUT_NORMAL_OPERATOR_DOMAIN_KRON
#define ONERUT_NORMAL_OPERATOR_DOMAIN_KRON

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {


    class KronPlaceholder;

    // -------------------------------------------------------------------------
    // --------------  Domain  -------------------------------------------------
    // -------------------------------------------------------------------------
    
    class KronDomain : public Domain {
    public:
        KronDomain(std::vector<std::shared_ptr<const Domain> > domains);
        unsigned size() const override;
        std::string state_name(unsigned index) const override;
        std::unique_ptr<KronPlaceholder> crate_placeholder(unsigned place) const;
    public:
        const std::vector<std::shared_ptr<const Domain> > domains;
        const std::vector<unsigned> domain_sizes;
        const std::vector<unsigned> weights;
    };

    // -------------------------------------------------------------------------
    // --------------  Placeholder  --------------------------------------------
    // -------------------------------------------------------------------------
    
    class KronPlaceholder {
    public:
        std::shared_ptr<const KronDomain> domain;
        unsigned place;
        std::shared_ptr<const Domain> fetch_domain() const;
    private:
        KronPlaceholder(std::shared_ptr<const KronDomain> domain, unsigned place);
        friend std::unique_ptr<KronPlaceholder> KronDomain::crate_placeholder(unsigned place) const;
    };

}

#endif
