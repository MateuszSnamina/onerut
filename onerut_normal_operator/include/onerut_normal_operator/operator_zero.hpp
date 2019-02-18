#ifndef ONERUT_NORMAL_OPERATOR_ZERO
#define ONERUT_NORMAL_OPERATOR_ZERO

#include<onerut_operator/operator_zero.hpp>

namespace onerut_normal_operator {
/*
    template<typename BraKetT>
    class ZeroOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = ZeroOperatorIterator<BraKetT>;
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    };

    template<typename BraKetT>
    class ZeroOperator : public AbstractOperator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = ZeroOperatorIterator<BraKetT>;
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    };

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------     

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type
    ZeroOperatorIterator<BraKetT>::get_val_bra() const {
        assert(!is_end());
        return std::make_pair(0, BraKetT());
    }

    template<typename BraKetT>
    void
    ZeroOperatorIterator<BraKetT>::next() {
        assert(!is_end());
    }

    template<typename BraKetT>
    bool
    ZeroOperatorIterator<BraKetT>::is_end() const {
        return true;
    }

    // -------------------------------------------------------------------------        

    template<typename BraKetT>
    typename ZeroOperator<BraKetT>::AbstractIteratorPtrT
    ZeroOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<Iterator>();
    }
*/
}

#endif
