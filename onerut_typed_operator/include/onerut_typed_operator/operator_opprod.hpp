#ifndef ONERUT_TYPED_OPERATOR_OPERATOR_OPPROD
#define ONERUT_TYPED_OPERATOR_OPERATOR_OPPROD

#include<onerut_typed_operator/operator_abstract.hpp>
#include<onerut_typed_operator/iterator_opprod.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ OpProd OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    class OpProdOperator : public AbstractOperator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = OpProdOperatorIterator<ScalarT, BraKetT, AbstractOpT>; //TODO: remove BraKetT when refactor OpProdOperatorIterator
        OpProdOperator(std::vector<AbstractOpPtrT> argv);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        std::vector<AbstractOpPtrT> argv;
    };

    // -------------------------------------------------------------------------
    // ------------------ Prod OPERATOR - implementation  ----------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    OpProdOperator<_ScalarT, _BraKetT>::OpProdOperator(std::vector<AbstractOpPtrT> argv) :
    argv(argv) {
    }

    template<typename _ScalarT, typename _BraKetT>
    typename OpProdOperator<_ScalarT, _BraKetT>::AbstractIteratorPtrT
    OpProdOperator<_ScalarT, _BraKetT>::begin_itptr(const BraKetT & ket) const {
        return std::make_unique<IteratorT>(argv, ket);
    }

}

#endif
