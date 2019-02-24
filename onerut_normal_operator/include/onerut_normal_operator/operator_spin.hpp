#ifndef ONERUT_NORMAL_OPERATOR_SPIN
#define ONERUT_NORMAL_OPERATOR_SPIN

#include<type_traits>

#include<onerut_typed_operator/iterator_simple.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class SpinDomain : public Domain {
    public:
        SpinDomain(unsigned multiplicity);
        //int n_stars_to_doubled_m(unsigned n_stars) const;
        const unsigned multiplicity;
        const unsigned n_max_stars;
    };

    // -------------------------------------------------------------------------

    class SpinZetOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<unsigned>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SpinZetOperator(std::shared_ptr<const SpinDomain> domain);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
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
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<unsigned>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SpinPlusOperator(std::shared_ptr<const SpinDomain> domain);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
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
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<unsigned>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SpinMinusOperator(std::shared_ptr<const SpinDomain> domain);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::shared_ptr<const SpinDomain> domain;
    };

}

#endif
