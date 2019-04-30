#ifndef ONERUT_NORMAL_OPERATOR_DOMAIN_FOCK
#define ONERUT_NORMAL_OPERATOR_DOMAIN_FOCK

#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    class OrbitalIndex;

    // -------------------------------------------------------------------------
    // --------------  Domain  -------------------------------------------------
    // -------------------------------------------------------------------------

    class FockDomain : public Domain {
    public:
        FockDomain(uint32_t n_particles, const std::vector<std::string > & orbital_names);
        uint32_t size() const override;
        std::string state_name(uint32_t index) const override;
        std::unique_ptr<OrbitalIndex> crate_orbital_index(uint32_t index) const;
    public:
        const uint32_t n_particles;
        const std::vector<std::string> orbital_names;
    };

    // -------------------------------------------------------------------------
    // --------------  OrbitalIndex  -------------------------------------------
    // -------------------------------------------------------------------------

    class OrbitalIndex {
    public:
        const std::shared_ptr<const FockDomain> domain;
        const unsigned index;
        std::string fetch_name() const;
    private:
        OrbitalIndex(std::shared_ptr<const FockDomain> domain, uint32_t inxed);
        friend std::unique_ptr<OrbitalIndex> FockDomain::crate_orbital_index(uint32_t index) const;
    };

}

#endif