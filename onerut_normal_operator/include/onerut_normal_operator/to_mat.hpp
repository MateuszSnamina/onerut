#ifndef ONERUT_NORMAL_OPERATOR_TO_MAT
#define ONERUT_NORMAL_OPERATOR_TO_MAT

#include<onerut_normal_operator/operator_abstract.hpp>

#include<armadillo>

namespace onerut_normal_operator {

    arma::mat to_mat(const AbstractOperator& op);

}

#endif
