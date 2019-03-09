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

    template<typename _ScalarT>
    class AbstractOperator : public onerut_typed_operator::AbstractOperator<_ScalarT, uint32_t> {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        virtual AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const = 0;
        virtual std::shared_ptr<const Domain> get_domain() const = 0;
    };

    using AbstractRealOperator = AbstractOperator<double>;
    
    // -------------------------------------------------------------------------
    // ----------------  Helper functions  -------------------------------------
    // -------------------------------------------------------------------------    

    bool are_the_same_domains(
            const std::shared_ptr<const AbstractRealOperator>& first_operator,
            const std::vector<std::shared_ptr<const AbstractRealOperator> >& other_operators);

    bool are_the_same_domains(
            const std::vector<std::shared_ptr<const AbstractRealOperator> >& operators);
}

#endif