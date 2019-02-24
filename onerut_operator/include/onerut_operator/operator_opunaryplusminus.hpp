#ifndef ONERUT_OPERATOR_OPUNARYPLUSMINUS
#define ONERUT_OPERATOR_OPUNARYPLUSMINUS

#include<onerut_operator/operator_abstract.hpp>
#include<onerut_operator/iterator_opunaryplusminus.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR  ---------------------------
    // -------------------------------------------------------------------------    

    template<typename _BraKetT>
    class OpUnaryPlusMinusOperator : public AbstractOperator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpUnaryPlusMinusOperatorIterator<BraKetT>;
        OpUnaryPlusMinusOperator(char op, AbstractOpPtrT arg);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const char op;
        const AbstractOpPtrT arg;
    };

    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR - IMPLEMENTATION -----------
    // -------------------------------------------------------------------------    

    template<typename _BraKetT>
    OpUnaryPlusMinusOperator<_BraKetT>::OpUnaryPlusMinusOperator(
            char op,
            AbstractOpPtrT arg) :
    op(op),
    arg(arg) {
    }

    template<typename _BraKetT>
    typename OpUnaryPlusMinusOperator<_BraKetT>::AbstractIteratorPtrT
    OpUnaryPlusMinusOperator<_BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<Iterator>(op, arg, ket);
    }

}

#endif
