#ifndef ONERUT_TYPED_OPERATOR_OPERATOR_OPSCALLED
#define ONERUT_TYPED_OPERATOR_OPERATOR_OPSCALLED

#include<onerut_typed_operator/operator_abstract.hpp>
#include<onerut_typed_operator/iterator_scalled.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename _BraKetT>
    class ScalledOperator : public AbstractOperator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>; 
        using Iterator = ScalledOperatorIterator<BraKetT>;
        ScalledOperator(double factor, AbstractOpPtrT arg);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const double factor;
        const AbstractOpPtrT arg;
    };

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------    

    template<typename _BraKetT>
    ScalledOperator<_BraKetT>::ScalledOperator(
            double factor,
            AbstractOpPtrT arg) :
    factor(factor),
    arg(arg) {
    }

    template<typename _BraKetT>
    typename ScalledOperator<_BraKetT>::AbstractIteratorPtrT
    ScalledOperator<_BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<Iterator>(factor, arg, ket);
    }

}

#endif
