#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_OPUNARYPLUSMINUS
#define ONERUT_NORMAL_OPERATOR_OPERATOR_OPUNARYPLUSMINUS

#include<type_traits>

#include<onerut_typed_operator/iterator_opunaryplusminus.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ------------------ OPUNARYPLUSMINUS OPERATOR  ---------------------------
    // -------------------------------------------------------------------------    

    class OpUnaryPlusMinusOperator : public AbstractRealOperator {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::OpUnaryPlusMinusOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        OpUnaryPlusMinusOperator(AbstractOpPtrT arg, char op);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    public:
        const AbstractOpPtrT arg;
        const char op;
    };

}

#endif
