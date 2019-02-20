#ifndef ONERUT_NORMAL_OPERATOR_OPSCALLED
#define ONERUT_NORMAL_OPERATOR_OPSCALLED

#include<onerut_operator/operator_scalled.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {
/*
    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    class ScalledOperator : public AbstractOperator {
    public:
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<unsigned>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = ScalledOperatorIterator<unsigned>;
        ScalledOperator(double factor, AbstractOpPtrT arg);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
    private:
        const double factor;
        const AbstractOpPtrT arg;
    };
*/
}

#endif
