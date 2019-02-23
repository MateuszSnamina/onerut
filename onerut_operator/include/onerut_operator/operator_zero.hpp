#ifndef ONERUT_OPERATOR_ZERO
#define ONERUT_OPERATOR_ZERO

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_operator {

    template<typename _BraKetT>
    class ZeroOperatorIterator : public AbstractResultIterator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;        
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = ZeroOperatorIterator<BraKetT>;
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    };

    template<typename _BraKetT>
    class ZeroOperator : public AbstractOperator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;
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

    template<typename _BraKetT>
    typename AbstractResultIterator<_BraKetT>::value_type
    ZeroOperatorIterator<_BraKetT>::get_val_bra() const {
        assert(!is_end());
        return std::make_pair(0, BraKetT());
    }

    template<typename _BraKetT>
    void
    ZeroOperatorIterator<_BraKetT>::next() {
        assert(!is_end());
    }

    template<typename _BraKetT>
    bool
    ZeroOperatorIterator<_BraKetT>::is_end() const {
        return true;
    }

    // -------------------------------------------------------------------------        

    template<typename _BraKetT>
    typename ZeroOperator<_BraKetT>::AbstractIteratorPtrT
    ZeroOperator<_BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<Iterator>();
    }

}

#endif
