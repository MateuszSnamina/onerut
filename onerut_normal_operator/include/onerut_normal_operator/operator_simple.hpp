#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_SIMPLE
#define ONERUT_NORMAL_OPERATOR_OPERATOR_SIMPLE

#include<type_traits>

#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_typed_operator/iterator_simple.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class HopOperator : public AbstractOperator<double> {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        HopOperator(std::shared_ptr<const onerut_scalar::Real> value,
                std::shared_ptr<const StateIndex> state_1,
                std::shared_ptr<const StateIndex> state_2);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const final;
        std::shared_ptr<const Domain> get_domain() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
    public:
        const std::shared_ptr<const onerut_scalar::Real> value;
        const std::shared_ptr<const StateIndex> state_1;
        const std::shared_ptr<const StateIndex> state_2;
    };

    class DiagOperator : public AbstractOperator<double> {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        DiagOperator(std::shared_ptr<const onerut_scalar::Real> value,
                std::shared_ptr<const StateIndex> state);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const final;
        std::shared_ptr<const Domain> get_domain() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
    public:
        const std::shared_ptr<const onerut_scalar::Real> value;
        const std::shared_ptr<const StateIndex> state;
    };

    class EyeOperator : public AbstractOperator<double> {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        EyeOperator(std::shared_ptr<const Domain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const final;
        std::shared_ptr<const Domain> get_domain() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
    public:
        const std::shared_ptr<const Domain> domain;
    };

}

#endif