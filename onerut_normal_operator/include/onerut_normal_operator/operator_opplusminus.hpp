#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_OPPLUSMINUS
#define ONERUT_NORMAL_OPERATOR_OPERATOR_OPPLUSMINUS

#include<type_traits>

#include<onerut_typed_operator/iterator_opplusminus.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------    

    class OpPlusMinusOperator : public AbstractRealOperator {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::OpPlusMinusOperatorIterator<ScalarT, BraKetT, AbstractOpT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        OpPlusMinusOperator(
                const AbstractOpPtrT& first_arg,
                const std::vector<AbstractOpPtrT>& other_argv,
                const std::vector<char>& opv);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    public:
        const AbstractOpPtrT first_arg;
        const std::vector<AbstractOpPtrT> other_argv;
        const std::vector<char> opv;
    };

}

#endif