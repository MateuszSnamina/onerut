#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_OPPROD
#define ONERUT_NORMAL_OPERATOR_OPERATOR_OPPROD

#include<type_traits>

#include<onerut_typed_operator/iterator_opprod.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ------------------ OpProd OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    class OpProdOperator : public AbstractOperator<double> {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::OpProdOperatorIterator<ScalarT, BraKetT, AbstractOpT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        OpProdOperator(std::vector<AbstractOpPtrT> argv);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    public:
        std::vector<AbstractOpPtrT> argv;
    };

}

#endif