#ifndef ONERUT_NORMAL_OPERATOR_OPPLUSMINUS
#define ONERUT_NORMAL_OPERATOR_OPPLUSMINUS

#include<onerut_operator/operator_opplusminus.hpp>

namespace onerut_operator {
/*
    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class OpPlusMinusOperator;

    template<typename BraKetT>
    class OpPlusMinusOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT>;
        OpPlusMinusOperatorIterator(
                const AbstractOpPtrT& first_arg,
                const std::vector<AbstractOpPtrT>& other_argv,
                const std::vector<char>& opv,
                const BraKetT& ket);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        AbstractIteratorPtrT _base_itptr;
        typename std::vector<AbstractOpPtrT>::const_iterator _other_argv_it;
        const typename std::vector<AbstractOpPtrT>::const_iterator _other_argv_end;
        std::vector<char>::const_iterator _opv_it;
        const BraKetT _ket;
        bool _process_first;
        void _goto_next_arg_if_base_itptr_is_end();
    };

    template<typename BraKetT>
    class OpPlusMinusOperator : public AbstractOperator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT>;
        OpPlusMinusOperator(
                const AbstractOpPtrT& first_arg,
                const std::vector<AbstractOpPtrT>& other_argv,
                const std::vector<char>& opv);
        std::unique_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const override;
    private:
        const AbstractOpPtrT first_arg;
        const std::vector<AbstractOpPtrT> other_argv;
        const std::vector<char> opv;
    };

*/
}

#endif
