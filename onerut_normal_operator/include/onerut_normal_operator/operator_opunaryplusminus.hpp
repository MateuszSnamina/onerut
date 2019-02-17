#ifndef ONERUT_NORMAL_OPERATOR_OPUNARYPLUSMINUS
#define ONERUT_NORMAL_OPERATOR_OPUNARYPLUSMINUS

#include<onerut_operator/operator_opunaryplusminus.hpp>

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

}

#endif
