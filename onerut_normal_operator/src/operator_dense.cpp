#include<cassert>

#include<onerut_normal_operator/operator_dense.hpp>

namespace onerut_normal_operator {

    DenseOperator::DenseOperator(std::shared_ptr<const Domain> domain, arma::mat matrix) :
    _domain(domain),
    _matrix(matrix) {
        assert(domain);
    }

    std::shared_ptr<const Domain> DenseOperator::get_domain() const {
        return _domain;
    }

    typename DenseOperator::AbstractIteratorPtrT
    DenseOperator::begin_itptr(const BraKetT& ket) const {
        assert(ket < _matrix.n_cols);
        return std::make_unique<IteratorT>(_matrix.col(ket));
    }

}