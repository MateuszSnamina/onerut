#include<gtest/gtest.h>

#include<onerut_typed_operator/operator_zero.hpp>
#include<onerut_typed_operator/operator_simple.hpp>
#include<onerut_typed_operator/operator_opprod.hpp>
#include<onerut_typed_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operatorOpProd, test0) {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const std::vector<OpPtrT> argv{};
    const auto op = std::make_shared<onerut_typed_operator::OpProdOperator<double, unsigned>>(argv);
    const arma::mat M_expected = arma::eye(4, 4);
    compare(M_expected, op);
}

TEST(operatorOpProd, test1) {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::ZeroOperator<double, unsigned>>();
    const std::vector<OpPtrT> argv{op1};
    const auto op = std::make_shared<onerut_typed_operator::OpProdOperator<double, unsigned>>(argv);
    const arma::mat M_expected(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operatorOpProd, test2) {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(3.2, 2, 1);
    const std::vector<OpPtrT> argv{op1};
    const auto op = std::make_shared<onerut_typed_operator::OpProdOperator<double, unsigned>>(argv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpProd, test3) {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(3.2, 2, 1);
    const auto op2 = std::make_shared<onerut_typed_operator::ZeroOperator<double, unsigned>>();
    const std::vector<OpPtrT> argv{op1, op2};
    const auto op = std::make_shared<onerut_typed_operator::OpProdOperator<double, unsigned>>(argv);
    const arma::mat M_expected(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operatorOpProd, test4) {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::ZeroOperator<double, unsigned>>();
    const auto op2 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(0.5, 2, 3);
    const std::vector<OpPtrT> argv{op1, op2};
    const auto op = std::make_shared<onerut_typed_operator::OpProdOperator<double, unsigned>>(argv);
    const arma::mat M_expected(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operatorOpProd, test5) {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(3.2, 2, 1);
    const auto op2 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(0.5, 2, 3);
    const std::vector<OpPtrT> argv{op1, op2};
    const auto op = std::make_shared<onerut_typed_operator::OpProdOperator<double, unsigned>>(argv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +1.6},
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpProd, test6) {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(3.2, 1, 0);
    const auto op2 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(0.5, 2, 1);
    const auto op3 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(4, 2, 3);
    const std::vector<OpPtrT> argv{op1, op2, op3};
    const auto op = std::make_shared<onerut_typed_operator::OpProdOperator<double, unsigned>>(argv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +6.4},
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpProd, test7) {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = first_compound_operator();
    const auto op2 = second_compound_operator();
    const std::vector<OpPtrT> argv{op1, op2};
    const auto op = std::make_shared<onerut_typed_operator::OpProdOperator<double, unsigned>>(argv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 * M2;
    compare(M_expected, op);
}

TEST(operatorOpProd, test8) {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = first_compound_operator();
    const auto op2 = second_compound_operator();
    const std::vector<OpPtrT> argv{op1, op2, op2};
    const auto op = std::make_shared<onerut_typed_operator::OpProdOperator<double, unsigned>>(argv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 * M2 * M2;
    compare(M_expected, op);
}