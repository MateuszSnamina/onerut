#ifndef ONERUT_NORMAL_OPERATOR_DIAGONALIZATOR
#define ONERUT_NORMAL_OPERATOR_DIAGONALIZATOR

#include<memory>
#include<armadillo>

#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    class Diagonalizator {
    public:
        Diagonalizator(std::shared_ptr<const AbstractOperator> hamiltonian);
        void diag(std::ostream& stream, std::string line_prefix = "");
        void print_energies(std::ostream& stream, unsigned chunk_size = 5, std::string line_prefix = "");
        void print_beta(std::ostream& stream, unsigned chunk_size = 5, std::string line_prefix = "");
        const arma::mat& get_beta() const;
        const arma::vec& get_energies() const;
        double get_mean(std::shared_ptr<const AbstractOperator> op) const;
    public:
        std::shared_ptr<const AbstractOperator> hamiltonian;
        arma::mat beta;
        arma::vec energies;
        std::vector<std::string> eig_names;
        bool success;
    };

}

#endif