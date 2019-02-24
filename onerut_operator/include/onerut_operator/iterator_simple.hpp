#ifndef ONERUT_ITERATOR_SIMPLE
#define ONERUT_ITERATOR_SIMPLE

#include<utility>
#include<optional>

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR --------------------------------------
    // -------------------------------------------------------------------------        

    template<typename _BraKetT>
    class SimpleOperatorIterator : public AbstractResultIterator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;        
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;        
        using Iterator = SimpleOperatorIterator<BraKetT>;        
        static SimpleOperatorIterator create_the_one_valid_iterator(typename AbstractResultIterator<BraKetT>::value_type);
        static SimpleOperatorIterator create_end_iterator();
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        SimpleOperatorIterator() = default;
        SimpleOperatorIterator(typename AbstractResultIterator<BraKetT>::value_type result);
        std::optional<std::pair<double, BraKetT>> result; // no value for the end iterator.
    };

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------     

    template<typename _BraKetT>
    SimpleOperatorIterator<_BraKetT>::SimpleOperatorIterator(typename AbstractResultIterator<BraKetT>::value_type result) :
    result(result) {
    }

    template<typename _BraKetT>
    SimpleOperatorIterator<_BraKetT>
    SimpleOperatorIterator<_BraKetT>::create_end_iterator() {
        return SimpleOperatorIterator<BraKetT>();
    }

    template<typename _BraKetT>
    SimpleOperatorIterator<_BraKetT>
    SimpleOperatorIterator<_BraKetT>::create_the_one_valid_iterator(typename AbstractResultIterator<BraKetT>::value_type result) {
        return SimpleOperatorIterator<BraKetT>(result);
    }

    template<typename _BraKetT>
    typename AbstractResultIterator<_BraKetT>::value_type
    SimpleOperatorIterator<_BraKetT>::get_val_bra() const {
        assert(result);
        return *result;
    }

    template<typename _BraKetT>
    void
    SimpleOperatorIterator<_BraKetT>::next() {
        assert(result);
        result.reset();
    }

    template<typename _BraKetT>
    bool
    SimpleOperatorIterator<_BraKetT>::is_end() const {
        return !result.has_value();
    }

}

#endif
