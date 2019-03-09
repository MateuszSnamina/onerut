#ifndef ONERUT_NORMAL_CALCULATE_MEAN
#define ONERUT_NORMAL_CALCULATE_MEAN

#include<armadillo>

#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    double calculate_mean(
            const AbstractRealOperator& op, const arma::vec& col);

    arma::vec many_calculate_mean(
            const AbstractRealOperator& op, const arma::mat& cols);

    arma::vec calculate_thermal_weights(
            arma::vec energies, double temperature);

    double calculate_thermal_mean(
            const AbstractRealOperator& op, const arma::mat& cols,
            const arma::vec& energies, double temperature);

}

#endif