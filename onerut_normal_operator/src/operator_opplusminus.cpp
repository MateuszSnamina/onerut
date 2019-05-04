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
        assert(other_argv.size() == opv.size());
        assert(are_the_same_domains(first_arg, other_argv));
    }

    typename OpPlusMinusOperator::AbstractIteratorPtrT
    OpPlusMinusOperator::begin_itptr(const BraKetT& ket) const {
        assert(are_the_same_domains(first_arg, other_argv));
        return std::make_unique<IteratorT>(first_arg, other_argv, opv, ket);
    }

    std::shared_ptr<const Domain>
    OpPlusMinusOperator::get_domain() const {
        return first_arg->get_domain();
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    OpPlusMinusOperator::dependence() const {
        decltype(dependence()) result;
        result.reserve(1 + other_argv.size());
        result.push_back(first_arg);
        for (const auto& other_arg : other_argv) {
            result.push_back(other_arg);
        }
        return result;
    }
}
