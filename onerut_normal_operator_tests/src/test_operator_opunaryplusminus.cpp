#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_opunaryplusminus.hpp>
#include<onerut_normal_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_opunaryplusminus, test_1) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(2.6_R, domain->crate_state(2), domain->crate_state(1));
    const auto op = std::make_shared<onerut_normal_operator::OpUnaryPlusMinusOperator>(op1, '+');
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 2.6, 0.0},
        {0.0, 2.6, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operator_opunaryplusminus, test_2) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::DiagOperator>(2.6_R, domain->crate_state(2));
    const auto op = std::make_shared<onerut_normal_operator::OpUnaryPlusMinusOperator>(op1, '-');
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, -2.6, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operator_opunaryplusminus, test_3) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = first_compound_operator(domain);
    const auto op = std::make_shared<onerut_normal_operator::OpUnaryPlusMinusOperator>(op1, '+');
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M_expected = +M1;
    compare(M_expected, op);
}

TEST(operator_opunaryplusminus, test_4) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = first_compound_operator(domain);
    const auto op = std::make_shared<onerut_normal_operator::OpUnaryPlusMinusOperator>(op1, '-');
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M_expected = -M1;
    compare(M_expected, op);
}

