#ifndef ONERUT_NORMAL_OPERATOR_ZERO
#define ONERUT_NORMAL_OPERATOR_ZERO

#include<onerut_operator/operator_zero.hpp>

//TODO source to cpp.

namespace onerut_normal_operator {

    class ZeroOperator : public AbstractOperator {
    public:
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_operator::AbstractResultIterator<unsigned>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = onerut_operator::ZeroOperatorIterator<unsigned>;
        ZeroOperator(std::shared_ptr<const Domain> domain);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const Domain> domain;
    };

    inline
    ZeroOperator::ZeroOperator(std::shared_ptr<const Domain> domain) :
    domain(domain) {
    }

    inline
    std::shared_ptr<const Domain> ZeroOperator::get_domain() const {
        return domain;
    }

    inline
    typename ZeroOperator::AbstractIteratorPtrT
    ZeroOperator::begin_itptr(const unsigned& ket) const {
        return std::make_unique<Iterator>();
    }

}

#endif
