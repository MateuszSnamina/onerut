#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_EG
#define ONERUT_NORMAL_OPERATOR_OPERATOR_EG

#include<type_traits>

#include<onerut_normal_operator/domain_eg.hpp>
#include<onerut_normal_operator/operator_dense.hpp>

namespace onerut_normal_operator {

    class SigmaXOperator : public DenseOperator {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = DenseIterator<ScalarT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SigmaXOperator(std::shared_ptr<const EgDomain> domain);
    };

    class SigmaZOperator : public DenseOperator {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = DenseIterator<ScalarT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        SigmaZOperator(std::shared_ptr<const EgDomain> domain);
    };

}

#endif