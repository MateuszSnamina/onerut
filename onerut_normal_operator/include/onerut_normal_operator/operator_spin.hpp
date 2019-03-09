#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_SPIN
#define ONERUT_NORMAL_OPERATOR_OPERATOR_SPIN

#include<type_traits>

#include<onerut_typed_operator/iterator_simple.hpp>
#include<onerut_normal_operator/utility_spin.hpp>
#include<onerut_normal_operator/domain_spin.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class SpinZetOperator : public AbstractRealOperator {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SpinZetOperator(std::shared_ptr<const SpinDomain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::shared_ptr<const SpinDomain> domain;
    };

    class SpinPlusOperator : public AbstractRealOperator {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SpinPlusOperator(std::shared_ptr<const SpinDomain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::shared_ptr<const SpinDomain> domain;
    };

    class SpinMinusOperator : public AbstractRealOperator {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SpinMinusOperator(std::shared_ptr<const SpinDomain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::shared_ptr<const SpinDomain> domain;
    };

}

#endif