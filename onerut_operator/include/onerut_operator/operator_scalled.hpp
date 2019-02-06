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
        ScalledOperatorIterator(double factor, std::shared_ptr<AbstractResultIterator<BraKetT>> base_itptr);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        const double factor;
        const std::shared_ptr<AbstractResultIterator<BraKetT>> base_itptr;
    };

    template<typename BraKetT>
    class ScalledOperator : public AbstractOperator<BraKetT> {
    public:
        using Iterator = ScalledOperatorIterator<BraKetT>;
        ScalledOperator(double factor, std::shared_ptr<const AbstractOperator<BraKetT>> arg);
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const override;
    private:
        const double factor;
        const std::shared_ptr<const AbstractOperator<BraKetT>> arg;
    };


    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    ScalledOperatorIterator<BraKetT>::ScalledOperatorIterator(
            double factor,
            std::shared_ptr<AbstractResultIterator<BraKetT>> base_itptr) :
    factor(factor),
    base_itptr(base_itptr) {
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
            std::shared_ptr<const AbstractOperator<BraKetT>> arg) :
    factor(factor),
    arg(arg) {
    }

    template<typename BraKetT>
    std::shared_ptr<AbstractResultIterator<BraKetT>>
    ScalledOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_shared<Iterator>(factor, arg->begin_itptr(ket));
    }

}

#endif
