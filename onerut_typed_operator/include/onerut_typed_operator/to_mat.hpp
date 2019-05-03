#ifndef ONERUT_TYPED_OPERATOR_TO_MAT
#define ONERUT_TYPED_OPERATOR_TO_MAT

#include<complex>
#include<armadillo>

#include<onerut_typed_operator/operator_abstract.hpp>

namespace onerut_typed_operator {

    arma::mat
    to_mat(const AbstractOperator<double, unsigned>& op,
            unsigned space_dim);

    arma::cx_mat
    to_mat(const AbstractOperator<std::complex<double>, unsigned>& op,
            unsigned space_dim);
}

#endif
