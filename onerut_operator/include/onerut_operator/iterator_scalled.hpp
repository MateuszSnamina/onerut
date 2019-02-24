#ifndef ONERUT_ITERATOR_OPSCALLED
#define ONERUT_ITERATOR_OPSCALLED

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename _BraKetT>
    class ScalledOperatorIterator : public AbstractResultIterator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = ScalledOperatorIterator<BraKetT>;
        ScalledOperatorIterator(double factor, const AbstractOpPtrT & arg, const BraKetT& ket);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        const double _factor;
        const AbstractIteratorPtrT _base_itptr;
    };

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------    

    template<typename _BraKetT>
    ScalledOperatorIterator<_BraKetT>::ScalledOperatorIterator(
            double factor,
            const AbstractOpPtrT & arg, const BraKetT& ket) :
    _factor(factor),
    _base_itptr(arg->begin_itptr(ket)) {
    }

    template<typename _BraKetT>
    typename AbstractResultIterator<_BraKetT>::value_type
    ScalledOperatorIterator<_BraKetT>::get_val_bra() const {
        assert(!_base_itptr->is_end());
        const auto& val_bra = _base_itptr->get_val_bra();
        const double& value = val_bra.first;
        const BraKetT& bra = val_bra.second;
        return std::make_pair(_factor*value, bra);
    }

    template<typename _BraKetT>
    void
    ScalledOperatorIterator<_BraKetT>::next() {
        assert(!_base_itptr->is_end());
        _base_itptr->next();
    }

    template<typename _BraKetT>
    bool
    ScalledOperatorIterator<_BraKetT>::is_end() const {
        return _base_itptr->is_end();
    }

}

#endif
