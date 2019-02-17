#ifndef ONERUT_NORMAL_OPERATOR_OPSCALLED
#define ONERUT_NORMAL_OPERATOR_OPSCALLED

#include<onerut_operator/operator_scalled.hpp>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class ScalledOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = ScalledOperatorIterator<BraKetT>;
        ScalledOperatorIterator(double factor, const AbstractOpPtrT & arg, const BraKetT& ket);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        const double _factor;
        const AbstractIteratorPtrT _base_itptr;
    };

    template<typename BraKetT>
    class ScalledOperator : public AbstractOperator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = ScalledOperatorIterator<BraKetT>;
        ScalledOperator(double factor, AbstractOpPtrT arg);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const double factor;
        const AbstractOpPtrT arg;
    };

}

#endif
