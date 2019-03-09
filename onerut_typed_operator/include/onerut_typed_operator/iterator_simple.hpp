#ifndef ONERUT_TYPED_OPERATOR_ITERATOR_SIMPLE
#define ONERUT_TYPED_OPERATOR_ITERATOR_SIMPLE

#include<optional>

#include<onerut_typed_operator/operator_abstract.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR --------------------------------------
    // -------------------------------------------------------------------------        

    template<typename _ScalarT, typename _BraKetT>
    class SimpleOperatorIterator : public AbstractResultIterator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = SimpleOperatorIterator<ScalarT, BraKetT>;
        static SimpleOperatorIterator create_the_one_valid_iterator(typename AbstractResultIterator<ScalarT, BraKetT>::value_type);
        static SimpleOperatorIterator create_end_iterator();
        typename AbstractResultIterator<ScalarT, BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        SimpleOperatorIterator() = default;
        SimpleOperatorIterator(typename AbstractResultIterator<ScalarT, BraKetT>::value_type result);
        std::optional<std::pair<ScalarT, BraKetT>> result; // no value for the end iterator.
    };

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------     

    template<typename _ScalarT, typename _BraKetT>
    SimpleOperatorIterator<_ScalarT, _BraKetT>::SimpleOperatorIterator(typename AbstractResultIterator<ScalarT, BraKetT>::value_type result) :
    result(result) {
    }

    template<typename _ScalarT, typename _BraKetT>
    SimpleOperatorIterator<_ScalarT, _BraKetT>
    SimpleOperatorIterator<_ScalarT, _BraKetT>::create_end_iterator() {
        return SimpleOperatorIterator<ScalarT, BraKetT>(); // TODO change into Iterator
    }

    template<typename _ScalarT, typename _BraKetT>
    SimpleOperatorIterator<_ScalarT, _BraKetT>
    SimpleOperatorIterator<_ScalarT, _BraKetT>::create_the_one_valid_iterator(typename AbstractResultIterator<ScalarT, BraKetT>::value_type result) {
        return SimpleOperatorIterator<ScalarT, BraKetT>(result); // TODO change into Iterator
    }

    template<typename _ScalarT, typename _BraKetT>
    typename AbstractResultIterator<_ScalarT, _BraKetT>::value_type
    SimpleOperatorIterator<_ScalarT, _BraKetT>::get_val_bra() const {
        assert(result);
        return *result;
    }

    template<typename _ScalarT, typename _BraKetT>
    void
    SimpleOperatorIterator<_ScalarT, _BraKetT>::next() {
        assert(result);
        result.reset();
    }

    template<typename _ScalarT, typename _BraKetT>
    bool
    SimpleOperatorIterator<_ScalarT, _BraKetT>::is_end() const {
        return !result.has_value();
    }

}

#endif
