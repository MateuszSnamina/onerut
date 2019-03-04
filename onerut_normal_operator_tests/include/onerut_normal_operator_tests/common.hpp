#ifndef ONERUT_OPERATOR_TEST_GLOBAL_COMMON
#define ONERUT_OPERATOR_TEST_GLOBAL_COMMON

#include<memory>
#include<armadillo>

#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_scalar/scalar_abstract_integer.hpp>
#include<onerut_normal_operator/domain_abstract.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

void compare(const arma::mat& M_expected, std::shared_ptr<onerut_normal_operator::AbstractOperator> op);

std::shared_ptr<onerut_scalar::Real> operator""_R(long double r);
std::shared_ptr<onerut_scalar::Integer> operator""_I(unsigned long long i);

std::shared_ptr<onerut_normal_operator::Domain> first_domain();
std::shared_ptr<onerut_normal_operator::Domain> second_domain();

arma::mat first_compound_matrix();
arma::mat second_compound_matrix();

std::shared_ptr<onerut_normal_operator::AbstractOperator> first_compound_operator(std::shared_ptr<onerut_normal_operator::Domain> domain);
std::shared_ptr<onerut_normal_operator::AbstractOperator> second_compound_operator(std::shared_ptr<onerut_normal_operator::Domain> domain);

#endif