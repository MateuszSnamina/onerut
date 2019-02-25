#ifndef ONERUT_NORMAL_OPERATOR_DIAGONALIZATOR
#define ONERUT_NORMAL_OPERATOR_DIAGONALIZATOR

#include<cassert> //to delete
#include<vector> //to delete
#include<string> //to delete

#include<memory>
#include<armadillo>

#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/to_mat.hpp> //to delete
#include<log_utils/fancy_log_mat.hpp> //to delete

namespace onerut_normal_operator {

    class Diagonalizator {
    public:
        Diagonalizator(std::shared_ptr<const AbstractOperator> hamiltonian);
        void diag();
        const arma::mat& get_beta() const;
        const arma::vec& get_energies() const;
        double get_mean(std::shared_ptr<const AbstractOperator> op) const;
    public:
        std::shared_ptr<const AbstractOperator> hamiltonian;
        arma::mat beta;
        arma::vec energies;
        bool success;
    };

    inline
    Diagonalizator::Diagonalizator(std::shared_ptr<const AbstractOperator> hamiltonian) :
    hamiltonian(hamiltonian) {
        assert(hamiltonian);
    }

    inline
    void Diagonalizator::diag() {
        std::cout << "[diagonalization] About to diagonalize." << std::endl;
        arma::mat hamiltonian_mat = to_mat(*hamiltonian);
        success = arma::eig_sym(energies, beta, hamiltonian_mat);
        if (!success) {
            std::cout << "[diagonalization] Fail to diagonalize." << std::endl;
        }

        //TODO: names creation to separate function
        std::vector<std::string> eig_names;
        eig_names.reserve(hamiltonian->get_domain()->size());
        for (unsigned i = 0; i < hamiltonian->get_domain()->size(); ++i) {
            eig_names.push_back("Eig" + std::to_string(i));
        }

        std::cout << energies;
        /*
        fancy_logging::log(std::cout,
                op.get_domain()->state_names,
                eig_names,
                beta,
                line_prefix);
         */
        fancy_logging::log(std::cout,
                hamiltonian->get_domain()->state_names,
                eig_names,
                beta,
                "[diagonalization]");
        std::cout << "[diagonalization] Has successfully diagonalized." << std::endl;

    }

}

#endif