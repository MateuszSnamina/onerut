#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_normal_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(mean, test0) {
    const auto domain = std::make_shared<onerut_normal_operator::CustomDomain>(std::vector<std::string>{"AA", "BB", "CC"});
    const auto hamiltonian = third_compound_operator(domain);
    const auto eig = std::make_shared<onerut_normal_operator::EigDense>(hamiltonian);
    const auto eig_result = eig->value();
    //-------
    {
        ASSERT_TRUE(eig_result.success);
    }
    //-------
    const auto treshold = 1e-14;
    //-------
    {
        const auto expected_beta = third_compound_matrix_eigenvectors();
        const auto got_beta = eig_result.beta;
        ASSERT_TRUE(expected_beta.n_rows == got_beta.n_rows);
        ASSERT_TRUE(expected_beta.n_cols == got_beta.n_cols);
        for (unsigned i = 0; i < expected_beta.n_cols; i++)
            EXPECT_TRUE(
                arma::norm(expected_beta.col(i) - got_beta.col(i)) < treshold ||
                arma::norm(expected_beta.col(i) + got_beta.col(i)) < treshold) << "(Eigenvector no " << i << " does not match.)";
    }
    //-------
    {
        const auto expected_energies = third_compound_matrix_eigenvalues();
        const auto got_energies = eig_result.energies;
        ASSERT_TRUE(expected_energies.n_elem == got_energies.n_elem);
        for (unsigned i = 0; i < expected_energies.n_elem; i++)
            EXPECT_NEAR(expected_energies(i), got_energies(i), treshold) << "(Eigenvalue no " << i << " does not match.)";
    }
    //------    
    const auto op = fourth_compound_operator(domain);
    {
        for (unsigned i = 0; i < op->get_domain()->size(); i++) {
            const auto mean = std::make_shared<onerut_normal_operator::MeanInEigenState>(eig, op, i);
            const auto expected_beta = third_compound_matrix_eigenvectors();
            const auto op_mat = fourth_compound_matrix();
            const auto expected_mean = arma::dot(expected_beta.col(i), op_mat * expected_beta.col(i));
            EXPECT_NEAR(expected_mean, mean->value_real(), treshold) << "(Mean in eigenstate no " << i << ")";
        }
    }

}


/*
TEST(eigSparse, test0) {
    const auto domain = std::make_shared<onerut_normal_operator::CustomDomain>(std::vector<std::string>{"AA", "BB", "CC"});
    const auto op = third_compound_operator(domain);
    const auto eig = std::make_shared<onerut_normal_operator::EigSparse>(op, 1);
    const auto eig_result = eig->value();
    //-------
    {
        ASSERT_TRUE(eig_result.success);
    }
    //-------
    const auto treshold = 1e-14;
    //-------
    {
        const auto expected_beta = third_compound_matrix_eigenvectors().cols(arma::span(0, 0));
        const auto got_beta = eig_result.beta;
        ASSERT_TRUE(expected_beta.n_rows == got_beta.n_rows);
        ASSERT_TRUE(expected_beta.n_cols == got_beta.n_cols);
        for (unsigned i = 0; i < expected_beta.n_cols; i++)
            EXPECT_TRUE(
                arma::norm(expected_beta.col(i) - got_beta.col(i)) < treshold ||
                arma::norm(expected_beta.col(i) + got_beta.col(i)) < treshold) << "(Eigenvector no " << i << " does not match.)";
    }
    //-------
    {
        const auto expected_energies = third_compound_matrix_eigenvalues().rows(arma::span(0, 0));
        const auto got_energies = eig_result.energies;
        ASSERT_TRUE(expected_energies.n_elem == got_energies.n_elem);
        for (unsigned i = 0; i < expected_energies.n_elem; i++)
            EXPECT_LT(std::abs(expected_energies(i) - got_energies(i)), treshold) << "(Eigenvalue no " << i << " does not match.)";
    }
}

TEST(eigSparse, test1) {
    const auto domain = std::make_shared<onerut_normal_operator::CustomDomain>(std::vector<std::string>{"AA", "BB", "CC"});
    const auto op = third_compound_operator(domain);
    const auto eig = std::make_shared<onerut_normal_operator::EigSparse>(op, 2);
    const auto eig_result = eig->value();
    //-------
    {
        ASSERT_TRUE(eig_result.success);
    }
    //-------
    const auto treshold = 1e-14;
    //-------
    {
        const auto expected_beta = third_compound_matrix_eigenvectors().cols(arma::span(0, 1));
        const auto got_beta = eig_result.beta;
        ASSERT_TRUE(expected_beta.n_rows == got_beta.n_rows);
        ASSERT_TRUE(expected_beta.n_cols == got_beta.n_cols);
        for (unsigned i = 0; i < expected_beta.n_cols; i++)
            EXPECT_TRUE(
                arma::norm(expected_beta.col(i) - got_beta.col(i)) < treshold ||
                arma::norm(expected_beta.col(i) + got_beta.col(i)) < treshold) << "(Eigenvector no " << i << " does not match.)";
    }
    //-------
    {
        const auto expected_energies = third_compound_matrix_eigenvalues().rows(arma::span(0, 1));
        const auto got_energies = eig_result.energies;
        ASSERT_TRUE(expected_energies.n_elem == got_energies.n_elem);
        for (unsigned i = 0; i < expected_energies.n_elem; i++)
            EXPECT_LT(std::abs(expected_energies(i) - got_energies(i)), treshold) << "(Eigenvalue no " << i << " does not match.)";
    }
}
 */
