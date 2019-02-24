#ifndef ONERUT_NORMAL_OPERATOR_ZERO
#define ONERUT_NORMAL_OPERATOR_ZERO

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
        using Iterator = onerut_typed_operator::ZeroOperatorIterator<unsigned>;
        ZeroOperator(std::shared_ptr<const Domain> domain);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const Domain> domain;
    };

}

#endif
