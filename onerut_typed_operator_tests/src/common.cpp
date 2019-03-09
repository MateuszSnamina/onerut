#include<gtest/gtest.h>

#include<onerut_typed_operator/operator_opplusminus.hpp>
#include<onerut_typed_operator/operator_simple.hpp>
#include<onerut_typed_operator/to_mat.hpp>

#include<onerut_typed_operator_tests/global_flags.hpp>
#include<onerut_typed_operator_tests/common.hpp>

extern bool onerut_verbose;

void compare(const arma::mat& M_expected, std::shared_ptr<onerut_typed_operator::AbstractOperator<double, unsigned>> op) {
    const arma::mat M_got = onerut_typed_operator::to_mat(*op, 4);
    if (onerut_verbose) {
        std::cout << "M_expected:" << std::endl;
        std::cout << M_expected;
        std::cout << "M_got:" << std::endl;
        std::cout << M_got;
    }
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            EXPECT_DOUBLE_EQ(M_got(i, j), M_expected(i, j)) << "(matrix element at position: row, col = " << i << ", " << j << ").";
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

std::shared_ptr<onerut_typed_operator::AbstractOperator<double, unsigned>> first_compound_operator() {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(3.2, 2, 1);
    auto op2 = std::make_shared<onerut_typed_operator::DiagOperator<double, unsigned>>(5.5, 1);
    auto op3 = std::make_shared<onerut_typed_operator::DiagOperator<double, unsigned>>(1.9, 2);
    auto op4 = std::make_shared<onerut_typed_operator::DiagOperator<double, unsigned>>(7, 0);
    OpPtrT op_first_arg = op1;
    std::vector<OpPtrT> op_other_argv({op2, op3, op4});
    std::vector<char> op_opv({'-', '+', '-'});
    auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<double, unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = first_compound_matrix();
    compare(M_expected, op);
    return op;
}

std::shared_ptr<onerut_typed_operator::AbstractOperator<double, unsigned>> second_compound_operator() {
    using OpT = onerut_typed_operator::AbstractOperator<double, unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(2.1, 2, 1);
    auto op2 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(1.1, 2, 3);
    auto op3 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(1.3, 2, 0);
    auto op4 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(2.3, 2, 1);
    auto op5 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(3.1, 2, 3);
    auto op6 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(3.3, 2, 3);
    auto op7 = std::make_shared<onerut_typed_operator::DiagOperator<double, unsigned>>(1.7, 2);
    OpPtrT op_first_arg = op1;
    std::vector<OpPtrT> op_other_argv({op2, op3, op4, op5, op6, op7});
    std::vector<char> op_opv({'+', '+', '+', '+', '+', '+'});
    auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<double, unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = second_compound_matrix();
    compare(M_expected, op);
    return op;
}
