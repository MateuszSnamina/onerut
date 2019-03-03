#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_OPUNARYPLUSMINUS
#define ONERUT_NORMAL_OPERATOR_OPERATOR_OPUNARYPLUSMINUS

#include<type_traits>

#include<onerut_typed_operator/iterator_opunaryplusminus.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR  ---------------------------
    // -------------------------------------------------------------------------    

    class OpUnaryPlusMinusOperator : public AbstractOperator {
    public:
        using AbstractOperator::BraKetT;
        using AbstractOperator::AbstractOpT;
        using AbstractOperator::AbstractOpPtrT;
        using AbstractOperator::AbstractIteratorT;
        using AbstractOperator::AbstractIteratorPtrT;
        using IteratorT = onerut_typed_operator::OpUnaryPlusMinusOperatorIterator<unsigned>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        OpUnaryPlusMinusOperator(AbstractOpPtrT arg, char op);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;        
    private:
        const AbstractOpPtrT arg;
        const char op;
    };

}

#endif
