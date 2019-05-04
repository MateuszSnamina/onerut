#include<cassert>

#include<onerut_normal_operator/operator_zero.hpp>

namespace onerut_normal_operator {

    ZeroOperator::ZeroOperator(std::shared_ptr<const Domain> domain) :
    domain(domain) {
    }

    std::shared_ptr<const Domain> ZeroOperator::get_domain() const {
        return domain;
    }

    typename ZeroOperator::AbstractIteratorPtrT
    ZeroOperator::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<IteratorT>();
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    ZeroOperator::dependence() const {
        return {};
    }

}
