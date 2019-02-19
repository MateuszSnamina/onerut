#include<cassert>

#include<onerut_normal_operator/operator_simple.hpp>

namespace onerut_normal_operator {

    HopOperator::HopOperator(std::shared_ptr<const onerut_scalar::Real> value,
            std::shared_ptr<const StateIndex> state_1,
            std::shared_ptr<const StateIndex> state_2
            ) :
    value(value),
    state_1(state_1),
    state_2(state_2) {
        assert(value);
        assert(state_1);
        assert(state_2);
        assert(&(*state_1->domain) == &(*state_2->domain)); // TODO: function encaptulation. TODO std::addressof
        assert(state_1->index != state_2->index);
    }

    std::shared_ptr<const Domain> HopOperator::get_domain() const {
        return state_1->domain;
    }

    typename HopOperator::AbstractIteratorPtrT
    HopOperator::begin_itptr(const unsigned& ket) const {
        if (ket == state_1->index) {
            return std::make_unique<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value->value_real(), state_2->index)));
        } else if (ket == state_2->index) {
            return std::make_unique<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value->value_real(), state_1->index)));
        }
        return std::make_unique<Iterator>(Iterator::create_end_iterator());
    }

    // -------------------------------------------------------------------------        

    DiagOperator::DiagOperator(std::shared_ptr<const onerut_scalar::Real> value,
            std::shared_ptr<const StateIndex> state) :
    value(value),
    state(state) {
    }

    std::shared_ptr<const Domain> DiagOperator::get_domain() const {
        return state->domain;
    }

    typename DiagOperator::AbstractIteratorPtrT
    DiagOperator::begin_itptr(const unsigned& ket) const {
        if (ket == state->index) {
            return std::make_unique<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value->value_real(), state->index)));
        }
        return std::make_unique<Iterator>(Iterator::create_end_iterator());
    }

}

