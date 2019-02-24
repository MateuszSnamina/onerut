#ifndef ONERUT_NORMAL_OPERATOR_OPSCALLED
#define ONERUT_NORMAL_OPERATOR_OPSCALLED

#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_typed_operator/iterator_scalled.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class ScalledOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using Iterator = onerut_typed_operator::ScalledOperatorIterator<unsigned>;
        ScalledOperator(std::shared_ptr<const onerut_scalar::Real> factor, AbstractOpPtrT arg);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;        
    private:
        const std::shared_ptr<const onerut_scalar::Real> factor;
        const AbstractOpPtrT arg;
    };

}

#endif
