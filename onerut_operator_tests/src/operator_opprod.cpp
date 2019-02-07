#include<gtest/gtest.h>

#include<onerut_operator/operator_opprod.hpp>
#include<onerut_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_op_prod, test_1) {

}

TEST(operator_op_prod, test_3) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op1 = first_compound_operator();
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op2 = second_compound_operator();
    std::vector<OpPtrT> argv({op1, op2});
    auto op = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(argv);
    const arma::mat M1 = {
        {-7.0, +0.0, +0.0, +0.0},
        {+0.0, -5.5, +3.2, +0.0},
        {+0.0, +3.2, +1.9, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    const arma::mat M2 = {
        {+0.0, +0.0, +1.3, +0.0},
        {+0.0, +0.0, +4.4, +0.0},
        {+1.3, +4.4, +1.7, +7.5},
        {+0.0, +0.0, +7.5, +0.0}
    };
    const arma::mat M_expected = M1 * M2;
    compare(M_expected, op);
}
