#ifndef ONERUT_NORMAL_OPERATOR_OPPROD
#define ONERUT_NORMAL_OPERATOR_OPPROD

#include<onerut_operator/operator_opprod.hpp>

namespace onerut_operator {
/*
    // -------------------------------------------------------------------------
    // ------------------ OpProd OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class OpProdOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpProdOperatorIterator<BraKetT>;
        OpProdOperatorIterator(
                const std::vector<AbstractOpPtrT>& argv, const BraKetT& ket);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        std::vector<AbstractOpPtrT> _argv;
        std::vector<AbstractIteratorPtrT> _base_itptr;
        std::vector<double> _factor;
        std::optional<BraKetT> _bra;
        std::optional<BraKetT> _init(unsigned arg_number, BraKetT);
        std::optional<BraKetT> _next(unsigned arg_number);
    };

    template<typename BraKetT>
    class OpProdOperator : public AbstractOperator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpProdOperatorIterator<BraKetT>;
        OpProdOperator(std::vector<AbstractOpPtrT> argv);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        std::vector<AbstractOpPtrT> argv;
    };

    // -------------------------------------------------------------------------

*/
}

#endif
