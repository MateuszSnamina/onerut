#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_ZERO
#define ONERUT_NORMAL_OPERATOR_OPERATOR_ZERO

#include<type_traits>

#include<onerut_typed_operator/iterator_zero.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class ZeroOperator : public AbstractOperator<double> {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::ZeroOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        ZeroOperator(std::shared_ptr<const Domain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const final;
        std::shared_ptr<const Domain> get_domain() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
    private:
        const std::shared_ptr<const Domain> domain;
    };

}

#endif