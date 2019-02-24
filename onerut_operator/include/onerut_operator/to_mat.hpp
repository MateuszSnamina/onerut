#ifndef ONERUT_OPERATOR_TO_MAT
#define ONERUT_OPERATOR_TO_MAT

#include<armadillo>

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_typed_operator {
    arma::mat to_mat(const AbstractOperator<unsigned>& op, unsigned spad_dim);
}

#endif
