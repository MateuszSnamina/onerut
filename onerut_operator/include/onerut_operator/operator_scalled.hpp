#ifndef ONERUT_OPERATOR_OPSCALLED
#define ONERUT_OPERATOR_OPSCALLED

#include<onerut_operator/operator_abstract.hpp>

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
        const double factor;
        const AbstractIteratorPtrT base_itptr;
    };

    template<typename BraKetT>
    class ScalledOperator : public AbstractOperator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;        
        using Iterator = ScalledOperatorIterator<BraKetT>;
        ScalledOperator(double factor, AbstractOpPtrT arg);
        std::unique_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const override;
    private:
        const double factor;
        const AbstractOpPtrT arg;
    };

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    ScalledOperatorIterator<BraKetT>::ScalledOperatorIterator(
            double factor,
            const AbstractOpPtrT & arg, const BraKetT& ket) :
    factor(factor),
    base_itptr(arg->begin_itptr(ket)) {
    }

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type
    ScalledOperatorIterator<BraKetT>::get_val_bra() const {
        assert(!base_itptr->is_end());
        const typename AbstractResultIterator<BraKetT>::value_type& val_bra = base_itptr->get_val_bra();
        const double& value = val_bra.first;
        const BraKetT& bra = val_bra.second;
        return std::make_pair(factor*value, bra);
    }

    template<typename BraKetT>
    void
    ScalledOperatorIterator<BraKetT>::next() {
        assert(!base_itptr->is_end());
        base_itptr->next();
    }

    template<typename BraKetT>
    bool
    ScalledOperatorIterator<BraKetT>::is_end() const {
        return base_itptr->is_end();
    }

    // -------------------------------------------------------------------------

    template<typename BraKetT>
    ScalledOperator<BraKetT>::ScalledOperator(
            double factor,
            AbstractOpPtrT arg) :
    factor(factor),
    arg(arg) {
    }

    template<typename BraKetT>
    std::unique_ptr<AbstractResultIterator<BraKetT>>
    ScalledOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<Iterator>(factor, arg, ket);
    }

}

#endif
