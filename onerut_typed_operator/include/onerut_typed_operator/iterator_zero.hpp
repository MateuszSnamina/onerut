#ifndef ONERUT_TYPED_OPERATOR_ITERATOR_ZERO
#define ONERUT_TYPED_OPERATOR_ITERATOR_ZERO

#include<onerut_typed_operator/operator_abstract.hpp>

namespace onerut_typed_operator {

    template<typename _ScalarT, typename _BraKetT>
    class ZeroOperatorIterator : public AbstractResultIterator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;        
        using BraKetT = _BraKetT;        
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = ZeroOperatorIterator<ScalarT, BraKetT>;
        typename AbstractResultIterator<ScalarT, BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    };

    // -------------------------------------------------------------------------
    // ------------------ ZERO OPERATOR - IMPLEMENTATION -----------------------
    // -------------------------------------------------------------------------     

    template<typename _ScalarT, typename _BraKetT>
    typename AbstractResultIterator<_ScalarT, _BraKetT>::value_type
    ZeroOperatorIterator<_ScalarT, _BraKetT>::get_val_bra() const {
        assert(!is_end());
        return std::make_pair(0, BraKetT());
    }

    template<typename _ScalarT, typename _BraKetT>
    void
    ZeroOperatorIterator<_ScalarT, _BraKetT>::next() {
        assert(!is_end());
    }

    template<typename _ScalarT, typename _BraKetT>
    bool
    ZeroOperatorIterator<_ScalarT, _BraKetT>::is_end() const {
        return true;
    }

}

#endif
