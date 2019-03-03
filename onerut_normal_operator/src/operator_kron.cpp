#include<cassert>

#include<onerut_normal_operator/operator_kron.hpp>

#include<iostream> //debug TODO delete

namespace {

    //    unsigned _get_site_intex(
    //            unsigned my_weight,
    //            unsigned next_weight,
    //            unsigned ket) {
    //        return (ket % next_weight) / my_weight;
    //    }
    //
    //    unsigned _get_site_intex(
    //            const std::vector<unsigned>& weights,
    //            unsigned site,
    //            unsigned ket) {
    //        assert(site < weights.size() - 1);
    //        return _get_site_intex(weights[site +1], weights[site], ket);
    //    }

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
        const BraKetT weight = 0;
        const BraKetT base = 0;
        const BraKetT subdomain_ket = 0;
        assert(0);
        //const AbstractOpPtrT& subdomain_op;
        //const BraKetT& subdomain_ket;
        return std::make_unique<IteratorT>(weight, base, subdomain_op, subdomain_ket);
    }

}

