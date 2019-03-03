#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_OSCILATOR
#define ONERUT_NORMAL_OPERATOR_OPERATOR_OSCILATOR

#include<type_traits>

#include<onerut_typed_operator/iterator_simple.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/domain_oscillator.hpp>

namespace onerut_normal_operator {

    class CreationOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<unsigned>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        CreationOperator(std::shared_ptr<const OscillatorDomain> domain);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::shared_ptr<const OscillatorDomain> domain;
    };

    class AnihilationOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<unsigned>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        AnihilationOperator(std::shared_ptr<const OscillatorDomain> domain);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::shared_ptr<const OscillatorDomain> domain;
    };
}

#endif
