#include<cassert>

#include<onerut_normal_operator/utility_kron.hpp>
#include<onerut_normal_operator/operator_kron.hpp>

namespace onerut_normal_operator {

    KronAtOperator::KronAtOperator(AbstractOpPtrT subdomain_op, std::shared_ptr<const KronPlaceholder> placeholder) :
    subdomain_op(subdomain_op),
    placeholder(placeholder) {

    }

    std::shared_ptr<const Domain> KronAtOperator::get_domain() const {
        return placeholder->domain;
    }

    typename KronAtOperator::AbstractIteratorPtrT
    KronAtOperator::begin_itptr(const BraKetT& ket) const {
        const unsigned place = placeholder->place;
        const BraKetT weight = placeholder->domain->get_place_weight(place);
        const auto & domain = placeholder->domain;
        const BraKetT subdomain_ket = utility::get_sub_index(*domain, place, ket);
        const BraKetT base = ket - subdomain_ket * weight;
        return std::make_unique<IteratorT>(weight, base, subdomain_op, subdomain_ket);
    }

}

