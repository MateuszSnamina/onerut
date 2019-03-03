#ifndef ONERUT_NROMAL_OPERATOR_ITERATOR_KRON
#define ONERUT_NROMAL_OPERATOR_ITERATOR_KRON

#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ------------------ KRON OPERATOR  ---------------------------------------
    // -------------------------------------------------------------------------    

    class KronIterator : public onerut_typed_operator::AbstractResultIterator<uint32_t> {
    public:
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<uint32_t>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = KronIterator;
        KronIterator(BraKetT weight, BraKetT base, const AbstractOpPtrT& subdomain_op, const BraKetT& subdomain_ket);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
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

    inline
    KronIterator::KronIterator(
            BraKetT weight,
            BraKetT base,
            const AbstractOpPtrT& subdomain_op,
            const BraKetT& subdomain_ket) :
    _weight(weight),
    _base(base),
    _subdomain_itptr(subdomain_op->begin_itptr(subdomain_ket)) {
    }

    inline
    typename KronIterator::AbstractIteratorT::value_type
    KronIterator::get_val_bra() const {
        assert(!_subdomain_itptr->is_end());
        const auto& subdomain_val_bra = _subdomain_itptr->get_val_bra();
        const double& value = subdomain_val_bra.first;
        const BraKetT& subdomain_bra = subdomain_val_bra.second;
        const BraKetT& bra = _base + _weight * subdomain_bra;
        return std::make_pair(value, bra);
    }

    inline
    void
    KronIterator::next() {
        assert(!_subdomain_itptr->is_end());
        _subdomain_itptr->next();
    }

    inline
    bool
    KronIterator::is_end() const {
        return _subdomain_itptr->is_end();
    }

}

#endif