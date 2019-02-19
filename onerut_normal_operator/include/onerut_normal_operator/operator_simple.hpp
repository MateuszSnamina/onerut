#ifndef ONERUT_NORMAL_OPERATOR_SIMPLE
#define ONERUT_NORMAL_OPERATOR_SIMPLE

#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

//TODO source to cpp.

namespace onerut_normal_operator {

    class HopOperator : public AbstractOperator {
    public:
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_operator::AbstractResultIterator<unsigned>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = onerut_operator::SimpleOperatorIterator<unsigned>;
        HopOperator(std::shared_ptr<const onerut_scalar::Real> value,
                std::shared_ptr<const StateIndex> state_1,
                std::shared_ptr<const StateIndex> state_2);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const onerut_scalar::Real> value;
        const std::shared_ptr<const Domain> domain;
        const unsigned site_1; // make simply std::shared_ptr<const StateIndex> state_1
        const unsigned site_2; // make simply std::shared_ptr<const StateIndex> state_2
    };

    class DiagOperator : public AbstractOperator {
    public:
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_operator::AbstractResultIterator<unsigned>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = onerut_operator::SimpleOperatorIterator<unsigned>;
        DiagOperator(std::shared_ptr<const onerut_scalar::Real> value,
                std::shared_ptr<const StateIndex> state);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const onerut_scalar::Real> value;
        const std::shared_ptr<const Domain> domain;
        const unsigned site;
    };


    // -------------------------------------------------------------------------    

    inline
    HopOperator::HopOperator(std::shared_ptr<const onerut_scalar::Real> value,
            std::shared_ptr<const StateIndex> state_1,
            std::shared_ptr<const StateIndex> state_2
            ) :
    value(value),
    domain(state_1->domain),
    site_1(state_1->index),
    site_2(state_2->index) {
        assert(value);
        assert(state_1);
        assert(state_2);
        assert(&(*state_1->domain) == &(*state_2->domain)); // TODO: function encaptulation. TODO std::addressof
        assert(state_1 != state_2);
    }

    inline
    std::shared_ptr<const Domain> HopOperator::get_domain() const {
        return domain;
    }

    inline
    typename HopOperator::AbstractIteratorPtrT
    HopOperator::begin_itptr(const unsigned& ket) const {
        if (ket == site_1) {
            return std::make_unique<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value->value_real(), site_2)));
        } else if (ket == site_2) {
            return std::make_unique<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value->value_real(), site_1)));
        }
        return std::make_unique<Iterator>(Iterator::create_end_iterator());
    }

    // -------------------------------------------------------------------------        

    inline
    DiagOperator::DiagOperator(std::shared_ptr<const onerut_scalar::Real> value,
            std::shared_ptr<const StateIndex> state) :
    value(value),
    domain(state->domain),
    site(state->index) {
    }

    inline
    std::shared_ptr<const Domain> DiagOperator::get_domain() const {
        return domain;
    }

    inline
    typename DiagOperator::AbstractIteratorPtrT
    DiagOperator::begin_itptr(const unsigned& ket) const {
        if (ket == site) {
            return std::make_unique<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value->value_real(), site)));
        }
        return std::make_unique<Iterator>(Iterator::create_end_iterator());
    }

}

#endif
