#ifndef ONERUT_TYPED_OPERATOR_OPERATOR_OPSCALLED
#define ONERUT_TYPED_OPERATOR_OPERATOR_OPSCALLED

#include<onerut_typed_operator/operator_abstract.hpp>
#include<onerut_typed_operator/iterator_scalled.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    class ScalledOperator : public AbstractOperator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = ScalledOperatorIterator<ScalarT, BraKetT>;
        ScalledOperator(ScalarT factor, AbstractOpPtrT arg);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const ScalarT factor;
        const AbstractOpPtrT arg;
    };

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    ScalledOperator<_ScalarT, _BraKetT>::ScalledOperator(
            ScalarT factor,
            AbstractOpPtrT arg) :
    factor(factor),
    arg(arg) {
    }

    template<typename _ScalarT, typename _BraKetT>
    typename ScalledOperator<_ScalarT, _BraKetT>::AbstractIteratorPtrT
    ScalledOperator<_ScalarT, _BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<IteratorT>(factor, arg, ket);
    }

}

#endif
