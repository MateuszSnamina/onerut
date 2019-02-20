#ifndef ONERUT_NORMAL_OPERATOR_OPPLUSMINUS
#define ONERUT_NORMAL_OPERATOR_OPPLUSMINUS

#include<onerut_operator/operator_opplusminus.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {
    
    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------    

    class OpPlusMinusOperator : public AbstractOperator {
    public:
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_operator::AbstractResultIterator<unsigned>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = onerut_operator::OpPlusMinusOperatorIterator<unsigned, AbstractOpT>;
        OpPlusMinusOperator(
                const AbstractOpPtrT& first_arg,
                const std::vector<AbstractOpPtrT>& other_argv,
                const std::vector<char>& opv);
        AbstractIteratorPtrT begin_itptr(const unsigned& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;        
    private:
        const AbstractOpPtrT first_arg;
        const std::vector<AbstractOpPtrT> other_argv;
        const std::vector<char> opv;
    };

}

#endif