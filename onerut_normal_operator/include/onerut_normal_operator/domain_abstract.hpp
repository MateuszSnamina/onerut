#ifndef ONERUT_NORMAL_OPERATOR_DOMAIN_ABSTRACT
#define ONERUT_NORMAL_OPERATOR_DOMAIN_ABSTRACT

#include<cstdint>
#include<memory>
#include<string>
#include<vector>

#include<onerut_typed_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // --------------  Domain  -------------------------------------------------
    // -------------------------------------------------------------------------

    struct StateIndex;

    class Domain : public std::enable_shared_from_this<Domain> {
    public:
        virtual uint32_t size() const = 0;
        virtual std::string state_name(uint32_t index) const = 0;
        virtual std::vector<std::string> state_names() const;
        std::unique_ptr<StateIndex> crate_state(uint32_t index) const;
    };

    // -------------------------------------------------------------------------
    // ----------------  StateIndex  -------------------------------------------
    // -------------------------------------------------------------------------

    struct StateIndex {
        const std::shared_ptr<const Domain> domain;
        const uint32_t index;
        std::string fetch_name() const;
        std::string to_str() const;
    private:
        StateIndex(std::shared_ptr<const Domain> domain, uint32_t index);
        friend std::unique_ptr<StateIndex> Domain::crate_state(uint32_t index) const;
    };

    // -------------------------------------------------------------------------
    // ----------------  Helper functions  -------------------------------------
    // -------------------------------------------------------------------------    

    bool are_the_same_domains(const Domain& first_domain, const Domain& second_domain);
    bool are_the_same_domains(const Domain& first_domain, const std::vector<Domain>& other_domains);
    bool are_the_same_domains(const std::vector<Domain>& domains);

}

#endif