#ifndef ONERUT_NROMAL_OPERATOR_ITERATOR_KRON
#define ONERUT_NROMAL_OPERATOR_ITERATOR_KRON

#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ------------------ KRON OPERATOR  ---------------------------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT>
    class KronIterator : public onerut_typed_operator::AbstractResultIterator<_ScalarT, uint32_t> {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<_ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = KronIterator;
        KronIterator(BraKetT weight, BraKetT base, const AbstractOpPtrT& subdomain_op, const BraKetT& subdomain_ket);
        typename AbstractIteratorT::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        const BraKetT _weight;
        const BraKetT _base;
        const AbstractIteratorPtrT _subdomain_itptr;
    };

    // -------------------------------------------------------------------------
    // ------------------ KRON OPERATOR - IMPLEMENTATION -----------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT>
    KronIterator<_ScalarT>::KronIterator(
            BraKetT weight,
            BraKetT base,
            const AbstractOpPtrT& subdomain_op,
            const BraKetT& subdomain_ket) :
    _weight(weight),
    _base(base),
    _subdomain_itptr(subdomain_op->begin_itptr(subdomain_ket)) {
    }

    template<typename _ScalarT>
    typename KronIterator<_ScalarT>::AbstractIteratorT::value_type
    KronIterator<_ScalarT>::get_val_bra() const {
        assert(!_subdomain_itptr->is_end());
        const auto& subdomain_val_bra = _subdomain_itptr->get_val_bra();
        const auto& value = subdomain_val_bra.first;
        const BraKetT& subdomain_bra = subdomain_val_bra.second;
        const BraKetT bra = _base + _weight * subdomain_bra;
        return std::make_pair(value, bra);
    }

    template<typename _ScalarT>
    void
    KronIterator<_ScalarT>::next() {
        assert(!_subdomain_itptr->is_end());
        _subdomain_itptr->next();
    }

    template<typename _ScalarT>
    bool
    KronIterator<_ScalarT>::is_end() const {
        return _subdomain_itptr->is_end();
    }

}

#endif