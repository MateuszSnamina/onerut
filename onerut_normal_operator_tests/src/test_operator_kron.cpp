#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/domain_kron.hpp>
#include<onerut_normal_operator/operator_zero.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_opprod.hpp>
#include<onerut_normal_operator/operator_kron.hpp>
#include<onerut_normal_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operatorKron, testTwoSubspaceTest0) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using SubDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto subdomain1 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC"});
    std::vector<DomainPtrT> subdomains = {subdomain0, subdomain1};
    const auto domain = std::make_shared<KronDomainT>(subdomains);
    const auto sub_op = std::make_shared<onerut_normal_operator::ZeroOperator>(subdomain0);
    const auto op = std::make_shared<onerut_normal_operator::KronAtOperator>(sub_op, domain->crate_placeholder(0));
    const arma::mat M_expected(12, 12, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operatorKron, testTwoSubspaceTest1) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using SubDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto subdomain1 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC"});
    std::vector<DomainPtrT> subdomains = {subdomain0, subdomain1};
    const auto domain = std::make_shared<KronDomainT>(subdomains);
    const auto sub_op = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, subdomain0->crate_state(2), subdomain0->crate_state(1));
    const auto op = std::make_shared<onerut_normal_operator::KronAtOperator>(sub_op, domain->crate_placeholder(0));
    const arma::mat sub0_M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    const arma::mat sub1_M_expected = arma::eye(3, 3);
    const arma::mat M_expected = arma::kron(sub0_M_expected, sub1_M_expected);
    compare(M_expected, op);
}

TEST(operatorKron, testTwoSubspaceTest2) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using SubDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto subdomain1 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC"});
    std::vector<DomainPtrT> subdomains = {subdomain0, subdomain1};
    const auto domain = std::make_shared<KronDomainT>(subdomains);
    const auto sub_op = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, subdomain1->crate_state(2), subdomain1->crate_state(1));
    const auto op = std::make_shared<onerut_normal_operator::KronAtOperator>(sub_op, domain->crate_placeholder(1));
    const arma::mat sub0_M_expected = arma::eye(4, 4);
    const arma::mat sub1_M_expected = {
        {+0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2},
        {+0.0, +3.2, +0.0}
    };
    const arma::mat M_expected = arma::kron(sub0_M_expected, sub1_M_expected);
    compare(M_expected, op);
}

TEST(operatorKron, testThreeSubpacesTest1) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using SubDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto subdomain1 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC"});
    const auto subdomain2 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD", "EE"});
    std::vector<DomainPtrT> subdomains = {subdomain0, subdomain1, subdomain2};
    const auto domain = std::make_shared<KronDomainT>(subdomains);
    const auto sub_op = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, subdomain0->crate_state(2), subdomain0->crate_state(1));
    const auto op = std::make_shared<onerut_normal_operator::KronAtOperator>(sub_op, domain->crate_placeholder(0));
    const arma::mat sub0_M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    const arma::mat sub1_M_expected = arma::eye(3, 3);
    const arma::mat sub2_M_expected = arma::eye(5, 5);
    const arma::mat M_expected = arma::kron(sub0_M_expected, arma::kron(sub1_M_expected, sub2_M_expected));
    compare(M_expected, op);
}

TEST(operatorKron, testThreeSubpacesTest2) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using SubDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto subdomain1 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC"});
    const auto subdomain2 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD", "EE"});
    std::vector<DomainPtrT> subdomains = {subdomain0, subdomain1, subdomain2};
    const auto domain = std::make_shared<KronDomainT>(subdomains);
    const auto sub_op = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, subdomain1->crate_state(2), subdomain1->crate_state(1));
    const auto op = std::make_shared<onerut_normal_operator::KronAtOperator>(sub_op, domain->crate_placeholder(1));
    const arma::mat sub0_M_expected = arma::eye(4, 4);
    const arma::mat sub1_M_expected = {
        {+0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2},
        {+0.0, +3.2, +0.0}
    };
    const arma::mat sub2_M_expected = arma::eye(5, 5);
    const arma::mat M_expected = arma::kron(sub0_M_expected, arma::kron(sub1_M_expected, sub2_M_expected));
    compare(M_expected, op);
}

TEST(operatorKron, testThreeSubpacesTest3) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using SubDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto subdomain1 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC"});
    const auto subdomain2 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD", "EE"});
    std::vector<DomainPtrT> subdomains = {subdomain0, subdomain1, subdomain2};
    const auto domain = std::make_shared<KronDomainT>(subdomains);
    const auto sub_op = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, subdomain2->crate_state(2), subdomain2->crate_state(1));
    const auto op = std::make_shared<onerut_normal_operator::KronAtOperator>(sub_op, domain->crate_placeholder(2));
    const arma::mat sub0_M_expected = arma::eye(4, 4);
    const arma::mat sub1_M_expected = arma::eye(3, 3);
    const arma::mat sub2_M_expected = {
        {+0.0, +0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0, +0.0},
        {+0.0, +3.2, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0, +0.0}
    };
    const arma::mat M_expected = arma::kron(sub0_M_expected, arma::kron(sub1_M_expected, sub2_M_expected));
    compare(M_expected, op);
}

TEST(operatorKron, testThreeSubpacesTest4) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using SubDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto subdomain1 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC"});
    const auto subdomain2 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD", "EE"});
    std::vector<DomainPtrT> subdomains = {subdomain0, subdomain1, subdomain2};
    const auto domain = std::make_shared<KronDomainT>(subdomains);
    const auto sub_op = second_compound_operator(subdomain0);
    const auto op = std::make_shared<onerut_normal_operator::KronAtOperator>(sub_op, domain->crate_placeholder(0));
    const arma::mat sub0_M_expected = second_compound_matrix();
    const arma::mat sub1_M_expected = arma::eye(3, 3);
    const arma::mat sub2_M_expected = arma::eye(5, 5);
    const arma::mat M_expected = arma::kron(sub0_M_expected, arma::kron(sub1_M_expected, sub2_M_expected));
    compare(M_expected, op);
}

TEST(operatorKron, testFourSubpacesTest1) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using SubDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC"});
    const auto subdomain1 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto subdomain2 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD", "EE"});
    const auto subdomain3 = std::make_shared<SubDomainT>(std::vector<std::string>{"AA", "BB"});
    std::vector<DomainPtrT> subdomains = {subdomain0, subdomain1, subdomain2, subdomain3};
    const auto domain = std::make_shared<KronDomainT>(subdomains);
    const auto sub_op = second_compound_operator(subdomain1);
    const auto op = std::make_shared<onerut_normal_operator::KronAtOperator>(sub_op, domain->crate_placeholder(1));
    const arma::mat sub0_M_expected = arma::eye(3, 3);
    const arma::mat sub1_M_expected = second_compound_matrix();
    const arma::mat sub2_M_expected = arma::eye(5, 5);
    const arma::mat sub3_M_expected = arma::eye(2, 2);
    const arma::mat M_expected = arma::kron(sub0_M_expected, arma::kron(sub1_M_expected, arma::kron(sub2_M_expected, sub3_M_expected)));
    compare(M_expected, op);
}