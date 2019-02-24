#include<cassert>
#include<onerut_normal_operator/operator_scalled.hpp>

namespace onerut_normal_operator {

    ScalledOperator::ScalledOperator(
            std::shared_ptr<const onerut_scalar::Real> factor,
            AbstractOpPtrT arg) :
    factor(factor),
    arg(arg) {
    }

    typename ScalledOperator::AbstractIteratorPtrT
    ScalledOperator::begin_itptr(const unsigned& ket) const {
        return std::make_unique<IteratorT>(factor->value_real(), arg, ket);
    }

    std::shared_ptr<const Domain> ScalledOperator::get_domain() const {
        return arg->get_domain();
    }
    
}
