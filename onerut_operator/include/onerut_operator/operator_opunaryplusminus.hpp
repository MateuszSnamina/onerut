#ifndef ONERUT_OPERATOR_OPUNARYPLUSMINUS
#define ONERUT_OPERATOR_OPUNARYPLUSMINUS

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR  ---------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class OpUnaryPlusMinusOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpUnaryPlusMinusOperatorIterator<BraKetT>;
        OpUnaryPlusMinusOperatorIterator(char op, const AbstractOpPtrT & arg, const BraKetT& ket);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        const char _op;
        const AbstractIteratorPtrT _base_itptr;
    };

    template<typename BraKetT>
    class OpUnaryPlusMinusOperator : public AbstractOperator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpUnaryPlusMinusOperatorIterator<BraKetT>;
        OpUnaryPlusMinusOperator(char op, AbstractOpPtrT arg);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const char op;
        const AbstractOpPtrT arg;
    };

    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR - IMPLEMENTATION -----------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    OpUnaryPlusMinusOperatorIterator<BraKetT>::OpUnaryPlusMinusOperatorIterator(
            char op,
            const AbstractOpPtrT & arg, const BraKetT& ket) :
    _op(op),
    _base_itptr(arg->begin_itptr(ket)) {
    }

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type
    OpUnaryPlusMinusOperatorIterator<BraKetT>::get_val_bra() const {
        assert(!_base_itptr->is_end());
        if (_op == '+') {
            return _base_itptr->get_val_bra();
        } else {
            assert(_op == '-');
            const auto& val_bra = _base_itptr->get_val_bra();
            const double& value = val_bra.first;
            const BraKetT& bra = val_bra.second;
            return std::make_pair(-value, bra);
        }
    }

    template<typename BraKetT>
    void
    OpUnaryPlusMinusOperatorIterator<BraKetT>::next() {
        assert(!_base_itptr->is_end());
        _base_itptr->next();
    }

    template<typename BraKetT>
    bool
    OpUnaryPlusMinusOperatorIterator<BraKetT>::is_end() const {
        return _base_itptr->is_end();
    }

    // -------------------------------------------------------------------------

    template<typename BraKetT>
    OpUnaryPlusMinusOperator<BraKetT>::OpUnaryPlusMinusOperator(
            char op,
            AbstractOpPtrT arg) :
    op(op),
    arg(arg) {
    }

    template<typename BraKetT>
    typename OpUnaryPlusMinusOperator<BraKetT>::AbstractIteratorPtrT
    OpUnaryPlusMinusOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<Iterator>(op, arg, ket);
    }

}

#endif
