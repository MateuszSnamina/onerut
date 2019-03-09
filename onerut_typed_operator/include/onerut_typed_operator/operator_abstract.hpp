#ifndef ONERUT_TYPED_OPERATOR_OPERATOR_ABSTRACT
#define ONERUT_TYPED_OPERATOR_OPERATOR_ABSTRACT

#include<memory>
#include<utility>

#include<onerut_typed_operator/iterator_abstract.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------  ABSTRACT OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------

    template<typename _ScalarT, typename _BraKetT>
    class AbstractOperator {
    public:
        using ScalarT = _ScalarT;        
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        virtual AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const = 0;
    };

}

#endif
