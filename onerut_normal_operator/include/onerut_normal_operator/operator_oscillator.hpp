#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_OSCILATOR
#define ONERUT_NORMAL_OPERATOR_OPERATOR_OSCILATOR

#include<type_traits>

#include<onerut_typed_operator/iterator_simple.hpp>
#include<onerut_normal_operator/domain_oscillator.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class CreationOperator : public AbstractOperator<double> {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        CreationOperator(std::shared_ptr<const OscillatorDomain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const final;
        std::shared_ptr<const Domain> get_domain() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
    private:
        std::shared_ptr<const OscillatorDomain> domain;
    };

    class AnihilationOperator : public AbstractOperator<double> {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        AnihilationOperator(std::shared_ptr<const OscillatorDomain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const final;
        std::shared_ptr<const Domain> get_domain() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
    private:
        std::shared_ptr<const OscillatorDomain> domain;
    };
}

#endif
