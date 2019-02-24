#ifndef ONERUT_TYPED_OPERATOR_OPERATOR_OPPLUSMINUS
#define ONERUT_TYPED_OPERATOR_OPERATOR_OPPLUSMINUS

#include<any>
#include<memory>
#include<algorithm>
#include<iterator>
#include<vector>
#include<optional>

#include<onerut_typed_operator/operator_abstract.hpp>
#include<onerut_typed_operator/iterator_opplusminus.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------    

    template<typename _BraKetT>
    class OpPlusMinusOperator : public AbstractOperator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT, AbstractOpT>;
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

    template<typename _BraKetT>
    OpPlusMinusOperator<_BraKetT>::OpPlusMinusOperator(
            const AbstractOpPtrT& first_arg,
            const std::vector<AbstractOpPtrT>& other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
    }

    template<typename _BraKetT>
    typename OpPlusMinusOperator<_BraKetT>::AbstractIteratorPtrT
    OpPlusMinusOperator<_BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<Iterator>(first_arg, other_argv, opv, ket);
    }

}

#endif
