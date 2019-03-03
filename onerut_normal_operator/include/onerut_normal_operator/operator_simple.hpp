#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_SIMPLE
#define ONERUT_NORMAL_OPERATOR_OPERATOR_SIMPLE

#include<type_traits>

#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_typed_operator/iterator_simple.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class HopOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<unsigned>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
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
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<unsigned>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        DiagOperator(std::shared_ptr<const onerut_scalar::Real> value,
                std::shared_ptr<const StateIndex> state);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const onerut_scalar::Real> value;
        const std::shared_ptr<const StateIndex> state;
    };

    class EyeOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<unsigned>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        EyeOperator(std::shared_ptr<const Domain> domain);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const Domain> domain;
    };

}

#endif
