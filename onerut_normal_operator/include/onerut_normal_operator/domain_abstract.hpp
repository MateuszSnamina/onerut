#ifndef ONERUT_NORMAL_DOMAIN_ABSTRACT
#define ONERUT_NORMAL_DOMAIN_ABSTRACT

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
        virtual unsigned size() const = 0;
        virtual std::string state_name(unsigned index) const = 0;
        virtual std::vector<std::string> state_names() const;
        std::unique_ptr<StateIndex> crate_state(unsigned index) const;
    };

    // -------------------------------------------------------------------------
    // ----------------  StateIndex  -------------------------------------------
    // -------------------------------------------------------------------------

    struct StateIndex {
        const std::shared_ptr<const Domain> domain;
        const unsigned index;
        std::string fetch_name() const;
        std::string to_str() const;
    private:
        StateIndex(std::shared_ptr<const Domain> domain, unsigned index);
        friend std::unique_ptr<StateIndex> Domain::crate_state(unsigned index) const;
    };

    // -------------------------------------------------------------------------
    // ----------------  Helper functions  -------------------------------------
    // -------------------------------------------------------------------------    

    bool are_the_same_domains(const Domain& first_domain, const Domain& second_domain);
    bool are_the_same_domains(const Domain& first_domain, const std::vector<Domain>& other_domains);
    bool are_the_same_domains(const std::vector<Domain>& domains);

}

#endif