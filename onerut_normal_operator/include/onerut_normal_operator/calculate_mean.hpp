#ifndef ONERUT_NORMAL_CALCULATE_MEAN
#define ONERUT_NORMAL_CALCULATE_MEAN

#include<armadillo>

#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    double calculate_mean(const AbstractOperator& op, const arma::vec& vec);

}

#endif
