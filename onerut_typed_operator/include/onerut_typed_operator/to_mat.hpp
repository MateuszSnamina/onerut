#ifndef ONERUT_TYPED_OPERATOR_TO_MAT
#define ONERUT_TYPED_OPERATOR_TO_MAT

#include<armadillo>

#include<onerut_typed_operator/operator_abstract.hpp>

namespace onerut_typed_operator {
    arma::mat to_mat(const AbstractOperator<unsigned>& op, unsigned spad_dim);
}

#endif
