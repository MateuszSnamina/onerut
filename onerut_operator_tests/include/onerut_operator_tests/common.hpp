#ifndef ONERUT_OPERATOR_TEST_GLOBAL_COMMON
#define ONERUT_OPERATOR_TEST_GLOBAL_COMMON

#include<memory>
#include<armadillo>

#include<onerut_operator/operator_abstract.hpp>

void compare(const arma::mat& M_expected, std::shared_ptr<onerut_typed_operator::AbstractOperator<unsigned>> op);

arma::mat first_compound_matrix();
arma::mat second_compound_matrix();

std::shared_ptr<onerut_typed_operator::AbstractOperator<unsigned>> first_compound_operator();
std::shared_ptr<onerut_typed_operator::AbstractOperator<unsigned>> second_compound_operator();

#endif
