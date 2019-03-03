#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_SPIN
#define ONERUT_NORMAL_OPERATOR_OPERATOR_SPIN

#include<type_traits>

#include<onerut_typed_operator/iterator_simple.hpp>
#include<onerut_normal_operator/utility_spin.hpp>
#include<onerut_normal_operator/domain_spin.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class SpinZetOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SpinZetOperator(std::shared_ptr<const SpinDomain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::shared_ptr<const SpinDomain> domain;
    };
    
    class SpinPlusOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SpinPlusOperator(std::shared_ptr<const SpinDomain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::shared_ptr<const SpinDomain> domain;
    };

    class SpinMinusOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SpinMinusOperator(std::shared_ptr<const SpinDomain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::shared_ptr<const SpinDomain> domain;
    };

}

#endif