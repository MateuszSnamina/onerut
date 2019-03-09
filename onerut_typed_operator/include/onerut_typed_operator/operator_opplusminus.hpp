#ifndef ONERUT_TYPED_OPERATOR_OPERATOR_OPPLUSMINUS
#define ONERUT_TYPED_OPERATOR_OPERATOR_OPPLUSMINUS

#include<onerut_typed_operator/operator_abstract.hpp>
#include<onerut_typed_operator/iterator_opplusminus.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    class OpPlusMinusOperator : public AbstractOperator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;        
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = OpPlusMinusOperatorIterator<ScalarT, BraKetT, AbstractOpT>;
        OpPlusMinusOperator(
                const AbstractOpPtrT& first_arg,
                const std::vector<AbstractOpPtrT>& other_argv,
                const std::vector<char>& opv);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const AbstractOpPtrT first_arg;
        const std::vector<AbstractOpPtrT> other_argv;
        const std::vector<char> opv;
    };

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR - implementation  -----------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    OpPlusMinusOperator<_ScalarT, _BraKetT>::OpPlusMinusOperator(
            const AbstractOpPtrT& first_arg,
            const std::vector<AbstractOpPtrT>& other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(other_argv.size() == opv.size());
    }

    template<typename _ScalarT, typename _BraKetT>
    typename OpPlusMinusOperator<_ScalarT, _BraKetT>::AbstractIteratorPtrT
    OpPlusMinusOperator<_ScalarT, _BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<IteratorT>(first_arg, other_argv, opv, ket);
    }

}

#endif
