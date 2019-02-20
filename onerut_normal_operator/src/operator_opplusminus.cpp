#include<cassert>
#include<onerut_normal_operator/operator_opplusminus.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------    

    OpPlusMinusOperator::OpPlusMinusOperator(
            const AbstractOpPtrT& first_arg,
            const std::vector<AbstractOpPtrT>& other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
    }

    typename OpPlusMinusOperator::AbstractIteratorPtrT
    OpPlusMinusOperator::begin_itptr(const unsigned& ket) const {
        return std::make_unique<Iterator>(first_arg, other_argv, opv, ket);
    }

    std::shared_ptr<const Domain> OpPlusMinusOperator::get_domain() const {
        return first_arg->get_domain();
    }

}
