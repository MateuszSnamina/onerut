#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_DENSE
#define ONERUT_NORMAL_OPERATOR_OPERATOR_DENSE

#include<type_traits>

#include<onerut_normal_operator/iterator_dense.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------

    class DenseOperator : public AbstractOperator<double> {
    public:       
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = DenseIterator<double>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        DenseOperator(std::shared_ptr<const Domain> domain, arma::mat matrix);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const std::shared_ptr<const Domain> _domain;
        const arma::mat _matrix;
    };

}

#endif