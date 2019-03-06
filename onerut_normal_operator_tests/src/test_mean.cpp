#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_normal_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(meanInEigenState, test0) {
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

TEST(meanThermal, test0) {
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
    const auto temperature = 0.85;
    const auto temperature_beta = 1.0 / 0.85;
    {
        double partition_function = 0.0;
        for (unsigned i = 0; i < op->get_domain()->size(); i++) {
            const auto expected_energies = third_compound_matrix_eigenvalues();
            partition_function += std::exp(-temperature_beta * expected_energies(i));
        }
        double expected_thermal_mean = 0.0;
        for (unsigned i = 0; i < op->get_domain()->size(); i++) {
            const auto op_mat = fourth_compound_matrix();
            const auto expected_energies = third_compound_matrix_eigenvalues();
            const auto expected_beta = third_compound_matrix_eigenvectors();
            const auto expected_state_mean = arma::dot(expected_beta.col(i), op_mat * expected_beta.col(i));
            expected_thermal_mean += std::exp(-temperature_beta * expected_energies(i)) / partition_function * expected_state_mean;
        }
        const auto mean = std::make_shared<onerut_normal_operator::MeanThermal>(eig, op, temperature);
        EXPECT_NEAR(expected_thermal_mean, mean->value_real(), treshold) << "(Thermal mean)";
    }
}
