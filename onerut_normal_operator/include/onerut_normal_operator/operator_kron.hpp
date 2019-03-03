#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_KRON
#define ONERUT_NORMAL_OPERATOR_OPERATOR_KRON

#include<type_traits>

#include<onerut_normal_operator/iterator_kron.hpp>
#include<onerut_normal_operator/domain_kron.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------

    class KronAtOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_normal_operator::KronIterator;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        KronAtOperator(AbstractOpPtrT subdomain_op, std::shared_ptr<const KronPlaceholder> placeholder);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const AbstractOpPtrT subdomain_op;
        const std::shared_ptr<const KronPlaceholder> placeholder;
    };

}

#endif
