#ifndef ONERUT_NORMAL_OPERATOR_SIMPLE
#define ONERUT_NORMAL_OPERATOR_SIMPLE

#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class HopOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using Iterator = onerut_operator::SimpleOperatorIterator<unsigned>;
        HopOperator(std::shared_ptr<const onerut_scalar::Real> value,
                std::shared_ptr<const StateIndex> state_1,
                std::shared_ptr<const StateIndex> state_2);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const onerut_scalar::Real> value;
        const std::shared_ptr<const StateIndex> state_1;
        const std::shared_ptr<const StateIndex> state_2;
    };

    class DiagOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using Iterator = onerut_operator::SimpleOperatorIterator<unsigned>;
        DiagOperator(std::shared_ptr<const onerut_scalar::Real> value,
                std::shared_ptr<const StateIndex> state);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const onerut_scalar::Real> value;
        const std::shared_ptr<const StateIndex> state;
    };

}

#endif
