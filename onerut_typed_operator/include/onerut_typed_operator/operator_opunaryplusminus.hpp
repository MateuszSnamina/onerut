#ifndef ONERUT_TYPED_OPERATOR_OPERATOR_OPUNARYPLUSMINUS
#define ONERUT_TYPED_OPERATOR_OPERATOR_OPUNARYPLUSMINUS

#include<onerut_typed_operator/operator_abstract.hpp>
#include<onerut_typed_operator/iterator_opunaryplusminus.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR  ---------------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    class OpUnaryPlusMinusOperator : public AbstractOperator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;        
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = OpUnaryPlusMinusOperatorIterator<ScalarT, BraKetT>;
        OpUnaryPlusMinusOperator(AbstractOpPtrT arg, char op);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const AbstractOpPtrT arg;
        const char op;
    };

    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR - IMPLEMENTATION -----------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    OpUnaryPlusMinusOperator<_ScalarT, _BraKetT>::OpUnaryPlusMinusOperator(
            AbstractOpPtrT arg,
            char op) :
    arg(arg),
    op(op) {
    }

    template<typename _ScalarT, typename _BraKetT>
    typename OpUnaryPlusMinusOperator<_ScalarT, _BraKetT>::AbstractIteratorPtrT
    OpUnaryPlusMinusOperator<_ScalarT, _BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<IteratorT>(op, arg, ket);
    }

}

#endif
