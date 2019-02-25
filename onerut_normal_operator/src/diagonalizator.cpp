#include<cassert>
#include<vector> 
#include<string> 

#include<log_utils/fancy_log_mat.hpp> 
#include<onerut_normal_operator/to_mat.hpp> 
#include<onerut_normal_operator/calculate_mean.hpp>
#include<onerut_normal_operator/diagonalizator.hpp>

namespace {

    std::vector<std::string> _eig_names(unsigned size) {
        std::vector<std::string> eig_names;
        eig_names.reserve(size);
        for (unsigned i = 0; i < size; ++i) {
            eig_names.push_back("Eig" + std::to_string(i));
        }
        return eig_names;
    }

}

namespace onerut_normal_operator {

    Diagonalizator::Diagonalizator(std::shared_ptr<const AbstractOperator> hamiltonian) :
    hamiltonian(hamiltonian) {
        assert(hamiltonian);
    }

    void Diagonalizator::diag(std::ostream& stream, std::string line_prefix) {
        // ---------------------------------------------------------------------
        stream << line_prefix << "[progress] About to diagonalize." << std::endl;
        // ---------------------------------------------------------------------
        eig_names = _eig_names(hamiltonian->get_domain()->size());
        // ---------------------------------------------------------------------
        const arma::mat hamiltonian_mat = to_mat(*hamiltonian);
        success = arma::eig_sym(energies, beta, hamiltonian_mat);
        if (!success) {
            stream << line_prefix << "[progress] Fail to diagonalize." << std::endl;
        }
        // ---------------------------------------------------------------------
        // Log the results:
        auto flags = stream.flags();
        stream << std::scientific << std::showpos;
        stream.width(10);
        const unsigned log_chunk_size = 5;
        print_energies(stream, log_chunk_size, line_prefix);
        print_beta(stream, log_chunk_size, line_prefix);
        stream.width(0);
        stream.flags(flags);
        // --------------------------------------------------------------------- 
        stream << line_prefix << "[progress] Has successfully diagonalized." << std::endl;
    }

    const arma::mat& Diagonalizator::get_beta() const {
        return beta;
    }

    const arma::vec& Diagonalizator::get_energies() const {
        return energies;
    }

    void Diagonalizator::print_energies(std::ostream& stream, unsigned chunk_size, std::string line_prefix) {
        fancy_logging::log(stream,{"Energy"}, eig_names,
                arma::trans(energies),
                chunk_size, line_prefix);
    }

    void Diagonalizator::print_beta(std::ostream& stream, unsigned chunk_size, std::string line_prefix) {
        fancy_logging::log(stream, hamiltonian->get_domain()->state_names, eig_names,
                beta,
                chunk_size, line_prefix);
    }

    double Diagonalizator::calculate_mean(std::shared_ptr<const AbstractOperator> op, unsigned eig_number) const {
        if (!op)
            return arma::datum::nan;
        if (eig_number >= beta.n_cols)
            return arma::datum::nan;
        return onerut_normal_operator::calculate_mean(*op, beta.col(eig_number));
    }

}
