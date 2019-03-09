#ifndef ONERUT_TYPED_OPERATOR_ITERATOR_ABSTRACT
#define ONERUT_TYPED_OPERATOR_ITERATOR_ABSTRACT

#include<memory>
#include<utility>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------  ABSTRACT OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------
    
    template<typename _ScalarT, typename _BraKetT>
    class AbstractOperator;

    template<typename _ScalarT, typename _BraKetT>
    class AbstractResultIterator {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = _BraKetT;
        using value_type = std::pair<_ScalarT, BraKetT>;
        using pointer = value_type*;
        using reference = value_type&;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        virtual value_type get_val_bra() const = 0;
        virtual void next() = 0;
        virtual bool is_end() const = 0;
        virtual ~AbstractResultIterator() = default;
    };

}

#endif
