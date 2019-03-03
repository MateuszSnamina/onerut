#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_ZERO
#define ONERUT_NORMAL_OPERATOR_OPERATOR_ZERO

#include<type_traits>

#include<onerut_typed_operator/iterator_zero.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class ZeroOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::ZeroOperatorIterator<BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        ZeroOperator(std::shared_ptr<const Domain> domain);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const Domain> domain;
    };

}

#endif