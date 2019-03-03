#include<cassert>

#include<onerut_normal_operator/operator_kron.hpp>

#include<iostream> //debug TODO delete

namespace {

    unsigned _get_site_intex(
            unsigned my_weight,
            unsigned next_weight,
            unsigned ket) {
        return (ket % next_weight) / my_weight;
    }

    unsigned _get_site_intex(
            const std::vector<unsigned>& weights,
            unsigned place,
            unsigned ket) {
        assert(place < weights.size() - 1);
        return _get_site_intex(weights[place + 1], weights[place], ket);
    }

}

namespace onerut_normal_operator {

    KronAtOperator::KronAtOperator(AbstractOpPtrT subdomain_op, std::shared_ptr<const KronPlaceholder> placeholder) :
    subdomain_op(subdomain_op),
    placeholder(placeholder) {

    }

    std::shared_ptr<const Domain> KronAtOperator::get_domain() const {
        return placeholder->domain;
    }

    typename KronAtOperator::AbstractIteratorPtrT
    KronAtOperator::begin_itptr(const unsigned& ket) const {
        const unsigned place = placeholder->place;
        const BraKetT weight = placeholder->domain->weights[place + 1];
        const BraKetT subdomain_ket = _get_site_intex(placeholder->domain->weights, place, ket);
        const BraKetT base = ket - subdomain_ket * weight;
        return std::make_unique<IteratorT>(weight, base, subdomain_op, subdomain_ket);
    }

}

