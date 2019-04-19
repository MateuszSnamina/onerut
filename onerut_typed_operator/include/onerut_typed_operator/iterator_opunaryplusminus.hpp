#ifndef ONERUT_TYPED_OPERATOR_ITERATOR_OPUNARYPLUSMINUS
#define ONERUT_TYPED_OPERATOR_ITERATOR_OPUNARYPLUSMINUS

#include<onerut_typed_operator/operator_abstract.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR  ---------------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    class OpUnaryPlusMinusOperatorIterator : public AbstractResultIterator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpUnaryPlusMinusOperatorIterator<ScalarT, BraKetT>;
        OpUnaryPlusMinusOperatorIterator(char op, const AbstractOpPtrT & arg, const BraKetT& ket);
        typename AbstractIteratorT::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        const char _op;
        const AbstractIteratorPtrT _base_itptr;
    };


    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR - IMPLEMENTATION -----------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    OpUnaryPlusMinusOperatorIterator<_ScalarT, _BraKetT>::OpUnaryPlusMinusOperatorIterator(
            char op,
            const AbstractOpPtrT & arg, const BraKetT& ket) :
    _op(op),
    _base_itptr(arg->begin_itptr(ket)) {
    }

    template<typename _ScalarT, typename _BraKetT>
    typename AbstractResultIterator<_ScalarT, _BraKetT>::value_type
    OpUnaryPlusMinusOperatorIterator<_ScalarT, _BraKetT>::get_val_bra() const {
        assert(!_base_itptr->is_end());
        if (_op == '+') {
            return _base_itptr->get_val_bra();
        } else {
            assert(_op == '-');
            const auto& val_bra = _base_itptr->get_val_bra();
            const auto& value = val_bra.first;
            const BraKetT& bra = val_bra.second;
            return std::make_pair(-value, bra);
        }
    }

    template<typename _ScalarT, typename _BraKetT>
    void
    OpUnaryPlusMinusOperatorIterator<_ScalarT, _BraKetT>::next() {
        assert(!_base_itptr->is_end());
        _base_itptr->next();
    }

    template<typename _ScalarT, typename _BraKetT>
    bool
    OpUnaryPlusMinusOperatorIterator<_ScalarT, _BraKetT>::is_end() const {
        return _base_itptr->is_end();
    }

}

#endif