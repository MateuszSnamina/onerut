#include<gtest/gtest.h>

#include<onerut_operator/operator_zero.hpp>
#include<onerut_operator/operator_simple.hpp>
#include<onerut_operator/operator_opprod.hpp>
#include<onerut_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_op_prod, test_0) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    std::vector<OpPtrT> argv{};
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M_expected = arma::eye(4, 4);
    compare(M_expected, op);
}

TEST(operator_op_prod, test_1) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_operator::ZeroOperator<unsigned>>();
    std::vector<OpPtrT> argv{op1};
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M_expected(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operator_op_prod, test_2) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(3.2, 2, 1);
    std::vector<OpPtrT> argv{op1};
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operator_op_prod, test_3) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(3.2, 2, 1);
    auto op2 = std::make_shared<onerut_operator::ZeroOperator<unsigned>>();
    std::vector<OpPtrT> argv{op1, op2};
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M_expected(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operator_op_prod, test_4) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_operator::ZeroOperator<unsigned>>();
    auto op2 = std::make_shared<onerut_operator::HopOperator<unsigned>>(0.5, 2, 3);
    std::vector<OpPtrT> argv{op1, op2};
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M_expected(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operator_op_prod, test_5) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(3.2, 2, 1);
    auto op2 = std::make_shared<onerut_operator::HopOperator<unsigned>>(0.5, 2, 3);
    std::vector<OpPtrT> argv{op1, op2};
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +1.6},
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operator_op_prod, test_6) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(3.2, 1, 0);
    auto op2 = std::make_shared<onerut_operator::HopOperator<unsigned>>(0.5, 2, 1);
    auto op3 = std::make_shared<onerut_operator::HopOperator<unsigned>>(4, 2, 3);
    std::vector<OpPtrT> argv{op1, op2, op3};
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +6.4},
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operator_op_prod, test_7) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op1 = first_compound_operator();
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op2 = second_compound_operator();
    std::vector<OpPtrT> argv{op1, op2};
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 * M2;
    compare(M_expected, op);
}

TEST(operator_op_prod, test_8) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op1 = first_compound_operator();
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op2 = second_compound_operator();
    std::vector<OpPtrT> argv{op1, op2, op2};
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 * M2 * M2;
    compare(M_expected, op);
}

