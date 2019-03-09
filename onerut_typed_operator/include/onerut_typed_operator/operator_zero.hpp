#ifndef ONERUT_TYPED_OPERATOR_OPERATOR_ZERO
#define ONERUT_TYPED_OPERATOR_OPERATOR_ZERO

#include<onerut_typed_operator/operator_abstract.hpp>
#include<onerut_typed_operator/iterator_zero.hpp>

namespace onerut_typed_operator {

    template<typename _ScalarT, typename _BraKetT>
    class ZeroOperator : public AbstractOperator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;        
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>; 
        using IteratorT = ZeroOperatorIterator<ScalarT, BraKetT>;
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    };

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------     

    template<typename _ScalarT, typename _BraKetT>
    typename ZeroOperator<_ScalarT, _BraKetT>::AbstractIteratorPtrT
    ZeroOperator<_ScalarT,_BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<IteratorT>();
    }

}

#endif
