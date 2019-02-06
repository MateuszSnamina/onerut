#ifndef ONERUT_TO_MAT
#define ONERUT_TO_MAT

#include<onerut_operator/operator_abstract.hpp>

#include<armadillo>

namespace onerut_operator {

    arma::mat to_mat(const AbstractOperator<unsigned>& op, unsigned spad_dim);
}

#endif
