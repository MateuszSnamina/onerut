#ifndef ONERUT_NROMAL_OPERATOR_ITERATOR_DENSE
#define ONERUT_NROMAL_OPERATOR_ITERATOR_DENSE

#include<armadillo>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ------------------ KRON OPERATOR  ---------------------------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT>
    class DenseIterator : public onerut_typed_operator::AbstractResultIterator<_ScalarT, uint32_t> {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<_ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = DenseIterator<double>;
        DenseIterator(arma::Col<_ScalarT> values);
        typename AbstractIteratorT::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        const arma::Col<_ScalarT> _values;
        arma::uword _current_index;
    };

    // -------------------------------------------------------------------------
    // ------------------ KRON OPERATOR - IMPLEMENTATION -----------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT>
    DenseIterator<_ScalarT>::DenseIterator(arma::Col<_ScalarT> values) :
    _values(values),
    _current_index(0) {
    }

    template<typename _ScalarT>
    typename DenseIterator<_ScalarT>::AbstractIteratorT::value_type
    DenseIterator<_ScalarT>::get_val_bra() const {
        assert(!is_end());
        const auto& value = _values[_current_index];
        const BraKetT ket = _current_index;
        return std::make_pair(value, ket);
    }

    template<typename _ScalarT>
    void
    DenseIterator<_ScalarT>::next() {
        assert(!is_end());
        ++_current_index;
    }

    template<typename _ScalarT>
    bool
    DenseIterator<_ScalarT>::is_end() const {
        return _current_index >= _values.n_elem;
    }

}

#endif