#ifndef ONERUT_NORMAL_OPERATOR_ABSTRACT
#define ONERUT_NORMAL_OPERATOR_ABSTRACT

#include<memory>
#include<string>
#include<vector>

#include<onerut_typed_operator/operator_abstract.hpp>
#include<onerut_normal_operator/domain_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ----------------  AbstractOperator  -------------------------------------
    // -------------------------------------------------------------------------    

    class AbstractOperator : public onerut_typed_operator::AbstractOperator<uint32_t> {
    public:
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        virtual AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const = 0;
        virtual std::shared_ptr<const Domain> get_domain() const = 0;
    };

    // -------------------------------------------------------------------------
    // ----------------  Helper functions  -------------------------------------
    // -------------------------------------------------------------------------    

    bool are_the_same_domains(
            const std::shared_ptr<const AbstractOperator>& first_operator,
            const std::vector<std::shared_ptr<const AbstractOperator> >& other_operators);
    
    bool are_the_same_domains(
            const std::vector<std::shared_ptr<const AbstractOperator> >& operators);
}

#endif