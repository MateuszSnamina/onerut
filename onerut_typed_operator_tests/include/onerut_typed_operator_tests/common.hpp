#ifndef ONERUT_TYPED_OPERATOR_TEST_COMMON
#define ONERUT_TYPED_OPERATOR_TEST_COMMON

#include<memory>
#include<armadillo>

#include<onerut_typed_operator/operator_abstract.hpp>

void compare(const arma::mat& M_expected, std::shared_ptr<onerut_typed_operator::AbstractOperator<double, unsigned>> op);

arma::mat first_compound_matrix();
arma::mat second_compound_matrix();

std::shared_ptr<onerut_typed_operator::AbstractOperator<double, unsigned>> first_compound_operator();
std::shared_ptr<onerut_typed_operator::AbstractOperator<double, unsigned>> second_compound_operator();

#endif
