#include<boost/cast.hpp>
#include<gtest/gtest.h>

#include<onerut_scalar/scalar_real.hpp>
#include<onerut_scalar/scalar_integer.hpp>
#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/operator_opplusminus.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/to_mat.hpp>

#include<onerut_normal_operator_tests/global_flags.hpp>
#include<onerut_normal_operator_tests/common.hpp>

extern bool onerut_verbose;

std::shared_ptr<onerut_scalar::Real>
operator""_R(long double r) {
    return std::make_shared<onerut_scalar::LitReal>(boost::numeric_cast<double>(r));
}

std::shared_ptr<onerut_scalar::Integer>
operator""_I(unsigned long long i) {
    return std::make_shared<onerut_scalar::LitInteger>(boost::numeric_cast<long>(i));
}

void compare(const arma::mat& M_expected, std::shared_ptr<onerut_normal_operator::AbstractOperator> op) {
    const arma::mat M_got = onerut_normal_operator::to_mat(*op);
    if (onerut_verbose) {
        std::cout << "M_got:" << std::endl;
        std::cout << M_got;
        std::cout << "M_expected:" << std::endl;
        std::cout << M_expected;
    }
    ASSERT_EQ(M_expected.n_rows, op->get_domain()->size());
    ASSERT_EQ(M_expected.n_cols, op->get_domain()->size());
    for (unsigned i = 0; i < M_expected.n_rows; i++)
        for (unsigned j = 0; j < M_expected.n_cols; j++)
            EXPECT_DOUBLE_EQ(M_got(i, j), M_expected(i, j)); //TODO add <<
}

arma::mat first_compound_matrix() {
    const arma::mat M = {
        {-7.0, +0.0, +0.0, +0.0},
        {+0.0, -5.5, +3.2, +0.0},
        {+0.0, +3.2, +1.9, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    return M;
}

arma::mat second_compound_matrix() {
    const arma::mat M = {
        {+0.0, +0.0, +1.3, +0.0},
        {+0.0, +0.0, +4.4, +0.0},
        {+1.3, +4.4, +1.7, +7.5},
        {+0.0, +0.0, +7.5, +0.0}
    };
    return M;
}

std::shared_ptr<onerut_normal_operator::AbstractOperator> first_compound_operator(std::shared_ptr<onerut_normal_operator::Domain> domain) {
    assert(domain->size() == 4);
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(2), domain->crate_state(1));
    auto op2 = std::make_shared<onerut_normal_operator::DiagOperator>(5.5_R, domain->crate_state(1));
    auto op3 = std::make_shared<onerut_normal_operator::DiagOperator>(1.9_R, domain->crate_state(2));
    auto op4 = std::make_shared<onerut_normal_operator::DiagOperator>(7_I, domain->crate_state(0));
    OpPtrT op_first_arg = op1;
    std::vector<OpPtrT> op_other_argv({op2, op3, op4});
    std::vector<char> op_opv({'-', '+', '-'});
    auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = first_compound_matrix();
    compare(M_expected, op);
    return op;
}

std::shared_ptr<onerut_normal_operator::AbstractOperator> second_compound_operator(std::shared_ptr<onerut_normal_operator::Domain> domain) {
    assert(domain->size() == 4);
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(2.1_R, domain->crate_state(2), domain->crate_state(1));
    auto op2 = std::make_shared<onerut_normal_operator::HopOperator>(1.1_R, domain->crate_state(2), domain->crate_state(3));
    auto op3 = std::make_shared<onerut_normal_operator::HopOperator>(1.3_R, domain->crate_state(2), domain->crate_state(0));
    auto op4 = std::make_shared<onerut_normal_operator::HopOperator>(2.3_R, domain->crate_state(2), domain->crate_state(1));
    auto op5 = std::make_shared<onerut_normal_operator::HopOperator>(3.1_R, domain->crate_state(2), domain->crate_state(3));
    auto op6 = std::make_shared<onerut_normal_operator::HopOperator>(3.3_R, domain->crate_state(2), domain->crate_state(3));
    auto op7 = std::make_shared<onerut_normal_operator::DiagOperator>(1.7_R, domain->crate_state(2));
    OpPtrT op_first_arg = op1;
    std::vector<OpPtrT> op_other_argv({op2, op3, op4, op5, op6, op7});
    std::vector<char> op_opv({'+', '+', '+', '+', '+', '+'});
    auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = second_compound_matrix();
    compare(M_expected, op);
    return op;
}

std::shared_ptr<onerut_normal_operator::Domain> first_domain() {
    using DomainT = onerut_normal_operator::CustomDomain;
    return std::make_shared<DomainT>(std::vector<std::string>{"1AA", "1BB", "1CC", "1DD"});
}

std::shared_ptr<onerut_normal_operator::Domain> second_domain() {
    using DomainT = onerut_normal_operator::CustomDomain;
    return std::make_shared<DomainT>(std::vector<std::string>{"2AA", "2BB", "2CC", "2DD", "5DD"});
}
