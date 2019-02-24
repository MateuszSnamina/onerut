#include<cassert>
#include<onerut_normal_operator/operator_opunaryplusminus.hpp>

namespace onerut_normal_operator {

    OpUnaryPlusMinusOperator::OpUnaryPlusMinusOperator(
            AbstractOpPtrT arg,
            char op) :
    arg(arg),
    op(op) {
    }

    typename OpUnaryPlusMinusOperator::AbstractIteratorPtrT
    OpUnaryPlusMinusOperator::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<IteratorT>(op, arg, ket);
    }

    std::shared_ptr<const Domain>
    OpUnaryPlusMinusOperator::get_domain() const {
        return arg->get_domain();
    }

}
