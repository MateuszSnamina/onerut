#ifndef ONERUT_NORMAL_OPERATOR_OPPROD
#define ONERUT_NORMAL_OPERATOR_OPPROD

#include<type_traits>

#include<onerut_typed_operator/iterator_opprod.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ------------------ OpProd OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    class OpProdOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::OpProdOperatorIterator<unsigned, AbstractOpT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        OpProdOperator(std::vector<AbstractOpPtrT> argv);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        std::vector<AbstractOpPtrT> argv;
    };

}

#endif
