#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_OPSCALLED
#define ONERUT_NORMAL_OPERATOR_OPERATOR_OPSCALLED

#include<type_traits>

#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_typed_operator/iterator_scalled.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class ScalledOperator : public AbstractRealOperator {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::ScalledOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        ScalledOperator(std::shared_ptr<const onerut_scalar::Real> factor, AbstractOpPtrT arg);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    public:
        const std::shared_ptr<const onerut_scalar::Real> factor;
        const AbstractOpPtrT arg;
    };

}

#endif