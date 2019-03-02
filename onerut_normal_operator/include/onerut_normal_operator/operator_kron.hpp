#ifndef ONERUT_NORMAL_OPERATOR_KRON
#define ONERUT_NORMAL_OPERATOR_KRON

#include<type_traits>

//#include<onerut_normal_operator/iterator_kron.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class KronDomain : public Domain {
    public:
        KronDomain(std::vector<std::shared_ptr<const Domain> > domains);
        unsigned size() const override;
        std::string state_name(unsigned index) const override;
        std::vector<std::shared_ptr<const Domain> > domains;
        const std::vector<unsigned> domain_sizes;
        const std::vector<unsigned> weights;
    };

    class SiteIndex {
    public:
        SiteIndex(std::shared_ptr<const KronDomain> domain, unsigned index); //TODO private
        unsigned index;
        std::shared_ptr<const KronDomain> domain;
    };

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
