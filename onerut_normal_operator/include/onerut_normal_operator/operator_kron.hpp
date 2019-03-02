#ifndef ONERUT_NORMAL_OPERATOR_KRON
#define ONERUT_NORMAL_OPERATOR_KRON

#include<type_traits>

//#include<onerut_normal_operator/iterator_kron.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/domain_kron.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    /*
        class KronAtOperator : public AbstractOperator {
        public:
            using AbstractOperator::BraKetT;
            using AbstractOperator::AbstractOpT;
            using AbstractOperator::AbstractOpPtrT;
            using AbstractOperator::AbstractIteratorT;
            using AbstractOperator::AbstractIteratorPtrT;
            using IteratorT = onerut_typed_operator::SimpleOperatorIterator<unsigned>;
            static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
            KronAtOperator(std::shared_ptr<const SpinDomain> domain);
            AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
            std::shared_ptr<const Domain> get_domain() const override;
        private:
            std::shared_ptr<const KronDomain> domain;
        };
     */
}

#endif
