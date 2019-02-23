#ifndef ONERUT_NORMAL_OPERATOR_ABSTRACT
#define ONERUT_NORMAL_OPERATOR_ABSTRACT

#include<memory>
#include<string>
#include<vector>

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // --------------  Domain  -------------------------------------------------
    // -------------------------------------------------------------------------

    struct StateIndex;

    class Domain : public std::enable_shared_from_this<Domain> {
    public:
        Domain(std::vector<std::string> state_names);
        unsigned size() const;
        std::unique_ptr<StateIndex> crate_state(unsigned index) const;
    public:
        const std::vector<std::string> state_names;
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
        StateIndex(unsigned index, std::shared_ptr<const Domain> domain);
        friend std::unique_ptr<StateIndex> Domain::crate_state(unsigned index) const;
    };

    // -------------------------------------------------------------------------
    // ----------------  AbstractOperator  -------------------------------------
    // -------------------------------------------------------------------------    

    class AbstractOperator : public onerut_operator::AbstractOperator<unsigned> {
    public:
        using typename onerut_operator::AbstractOperator<unsigned>::BraKetT;
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using typename onerut_operator::AbstractOperator<unsigned>::AbstractIteratorT;
        using typename onerut_operator::AbstractOperator<unsigned>::AbstractIteratorPtrT;
        virtual std::shared_ptr<const Domain> get_domain() const = 0;
    };

    // -------------------------------------------------------------------------
    // ----------------  Helper functions  -------------------------------------
    // -------------------------------------------------------------------------    

    bool are_the_same_domains(const Domain& first_domain, const Domain& second_domain);
    bool are_the_same_domains(const Domain& first_domain, const std::vector<Domain>& other_domains);
    bool are_the_same_domains(
            const std::shared_ptr<const AbstractOperator>& first_operator,
            const std::vector<std::shared_ptr<const AbstractOperator> >& other_operators);

}



#endif