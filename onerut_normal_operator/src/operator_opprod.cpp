#include<cassert>
#include<onerut_normal_operator/operator_opprod.hpp>

namespace onerut_normal_operator {

    OpProdOperator::OpProdOperator(std::vector<AbstractOpPtrT> argv) :
    argv(argv) {
        assert(are_the_same_domains(argv));
    }

    typename OpProdOperator::AbstractIteratorPtrT
    OpProdOperator::begin_itptr(const BraKetT& ket) const {
        assert(are_the_same_domains(argv));
        return std::make_unique<IteratorT>(argv, ket);
    }

    std::shared_ptr<const Domain>
    OpProdOperator::get_domain() const {
        return (argv.empty() ? std::shared_ptr<const Domain>(nullptr) : argv[0]->get_domain());
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    OpProdOperator::dependence() const {
        decltype(dependence()) result;
        result.reserve(argv.size());
        for (const auto& other_arg : argv) {
            result.push_back(other_arg);
        }
        return result;
    }

}