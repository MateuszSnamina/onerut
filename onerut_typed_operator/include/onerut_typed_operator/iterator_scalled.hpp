#ifndef ONERUT_TYPED_OPERATOR_ITERATOR_OPSCALLED
#define ONERUT_TYPED_OPERATOR_ITERATOR_OPSCALLED

#include<onerut_typed_operator/operator_abstract.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    class ScalledOperatorIterator : public AbstractResultIterator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;        
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = ScalledOperatorIterator<ScalarT, BraKetT>;
        ScalledOperatorIterator(ScalarT factor, const AbstractOpPtrT & arg, const BraKetT& ket);
        typename AbstractResultIterator<ScalarT, BraKetT>::value_type get_val_bra() const override; //TODO use  AbstractIteratorT
        void next() override;
        virtual bool is_end() const override;
    private:
        const ScalarT _factor;
        const AbstractIteratorPtrT _base_itptr;
    };

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT>
    ScalledOperatorIterator<_ScalarT, _BraKetT>::ScalledOperatorIterator(
            ScalarT factor,
            const AbstractOpPtrT & arg, const BraKetT& ket) :
    _factor(factor),
    _base_itptr(arg->begin_itptr(ket)) {
    }

    template<typename _ScalarT, typename _BraKetT>
    typename AbstractResultIterator<_ScalarT, _BraKetT>::value_type
    ScalledOperatorIterator<_ScalarT, _BraKetT>::get_val_bra() const {
        assert(!_base_itptr->is_end());
        const auto& val_bra = _base_itptr->get_val_bra();
        const auto& value = val_bra.first;
        const BraKetT& bra = val_bra.second;
        return std::make_pair(_factor*value, bra);
    }

    template<typename _ScalarT, typename _BraKetT>
    void
    ScalledOperatorIterator<_ScalarT, _BraKetT>::next() {
        assert(!_base_itptr->is_end());
        _base_itptr->next();
    }

    template<typename _ScalarT, typename _BraKetT>
    bool
    ScalledOperatorIterator<_ScalarT, _BraKetT>::is_end() const {
        return _base_itptr->is_end();
    }

}

#endif
