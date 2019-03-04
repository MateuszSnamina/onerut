#include<cassert>
#include<vector> 
#include<string> 
#include<boost/cast.hpp>

#include<log_utils/fancy_log_mat.hpp> 
#include<onerut_normal_operator/to_mat.hpp> 
#include<onerut_normal_operator/eig.hpp>

namespace {

    std::vector<std::string> _eig_names(uint32_t size) {
        std::vector<std::string> eig_names;
        eig_names.reserve(size);
        for (uint32_t i = 0; i < size; ++i) {
            eig_names.push_back("Eig" + std::to_string(i));
        }
        return eig_names;
    }

}

namespace onerut_normal_operator {

    // *************************************************************************
    // *************  Eig   ****************************************************
    // *************************************************************************

    void EigResult::print_energies(std::ostream& stream, unsigned chunk_size, std::string line_prefix) const {
        fancy_logging::log(stream,{"Energy"}, eig_names,
                arma::trans(energies),
                chunk_size, line_prefix);
    }

    void EigResult::print_beta(std::ostream& stream, unsigned chunk_size, std::string line_prefix) const {
        fancy_logging::log(stream, hamiltonian->get_domain()->state_names(), eig_names,
                beta,
                chunk_size, line_prefix);
    }

    void EigResult::log(std::ostream& stream, std::string line_prefix) const {
        auto flags = stream.flags();
        stream << std::scientific << std::showpos;
        stream.width(10);
        const unsigned log_chunk_size = 5;
        print_energies(stream, log_chunk_size, line_prefix);
        print_beta(stream, log_chunk_size, line_prefix);
        stream.width(0);
        stream.flags(flags);
    }

    // *************************************************************************

    Eig::Eig(std::shared_ptr<const AbstractOperator> hamiltonian) :
    hamiltonian(hamiltonian),
    cached_result(std::nullopt) {
        assert(hamiltonian);
    }

    EigResult Eig::value() const {
        return ( cached_result ? *cached_result : _value());
    }

    void Eig::latch() {
        cached_result.emplace(_value());
    }

    void Eig::reset() {
        cached_result = std::nullopt;
    }

    // *************************************************************************

    EigDense::EigDense(std::shared_ptr<const AbstractOperator> hamiltonian) :
    Eig(hamiltonian) {
    }

    EigResult EigDense::_value() const {
        // ---------------------------------------------------------------------
        const std::vector<std::string> eig_names = _eig_names(hamiltonian->get_domain()->size());
        // ---------------------------------------------------------------------
        arma::vec energies;
        arma::mat beta;
        const arma::mat hamiltonian_mat = to_mat(*hamiltonian);
        const bool success = arma::eig_sym(energies, beta, hamiltonian_mat);
        // ---------------------------------------------------------------------
        const EigResult result = {hamiltonian, success, eig_names, energies, beta};
        return result;
    }

    // *************************************************************************

    EigSparse::EigSparse(
            std::shared_ptr<const AbstractOperator> hamiltonian,
            std::shared_ptr<const onerut_scalar::Integer> numer_of_states_to_calculate) :
    Eig(hamiltonian),
    numer_of_states_to_calculate(numer_of_states_to_calculate) {
    }

    EigResult EigSparse::_value() const {
        // ------------------------------
        const auto requested_numer_of_states_to_calculate =
                boost::numeric_cast<arma::uword>(numer_of_states_to_calculate->value_integer());
        const auto space_dim =
                boost::numeric_cast<arma::uword>(hamiltonian->get_domain()->size());
        // ---------------------------------------------------------------------
        const std::vector<std::string> eig_names =
                _eig_names(numer_of_states_to_calculate->value_integer());
        arma::vec energies;
        arma::mat beta;
        bool success = false;
        // ---------------------------------------------------------------------        
        if (requested_numer_of_states_to_calculate >= space_dim) {
            std::cout << "[INFO   ] [SPARSE] The requested numer of states to calculate is too big." << std::endl;
            const EigResult result = {hamiltonian, success, eig_names, energies, beta};
            return result;
        }
        // ---------------------------------------------------------------------
        const auto hamiltonian_sp_mat = to_sp_mat(*hamiltonian);
        success = arma::eigs_sym(energies, beta, hamiltonian_sp_mat,
                requested_numer_of_states_to_calculate, "sa");
        // ------------------------------
        if (!success) { // Arma reports en error.
            std::cout << "[INFO   ] [SPARSE] Armadillo failed to diagonalize the hamiltonian (and reported an error)!" << std::endl;
            if (hamiltonian_sp_mat.n_rows < 100) {
                // Fall-back -> use dense calculation for small matrices.
                std::cout << "[INFO   ] [SPARSE] [FALL-BACK] Armadillo will try to diagonalize the hamiltonian as a dense matrix.";
                const auto hamiltonian_mat = to_mat(*hamiltonian);
                success = arma::eig_sym(energies, beta, hamiltonian_mat);
                if (success) {
                    std::cout << "[INFO   ] [SPARSE] [FALL-BACK] The fall-back succeeded.";
                } else {
                    std::cout << "[INFO   ] [SPARSE] [FALL-BACK] The fall-back failed.";
                }
            } else {
                std::cout << "[INFO   ] [SPARSE] [FALL-BACK] The matrix is to big for a dense matrix fall-back.";
            }
        } else { // Arma does not report en error.
            if (energies.n_elem < requested_numer_of_states_to_calculate) {
                // Fall-back -> increase requested_numer_of_states_to_calculate.                
                // ... TODO
                std::cout << "[INFO   ] [SPARSE] Armadillo failed to diagonalize the hamiltonian (but not reported an error)!" << std::endl;
                std::cout << "[INFO   ] [SPARSE] [FALL-BACK] The program is about to diagonalize the hamiltonian with grater n_calculated_states requested." << std::endl;
                const auto second_try_requested_numer_of_states_to_calculate =
                        std::min(requested_numer_of_states_to_calculate + 5, space_dim - 1);
                success = arma::eigs_sym(energies, beta, hamiltonian_sp_mat,
                        second_try_requested_numer_of_states_to_calculate, "sa");
                if (success) {
                    std::cout << "[INFO   ] [SPARSE] [FALL-BACK] The fall-back succeeded.";
                } else {
                    std::cout << "[INFO   ] [SPARSE] [FALL-BACK] The fall-back failed.";
                }
            }
        }
        // ------------------------------
        assert(energies.n_elem == beta.n_cols);
        assert(energies.n_elem >= requested_numer_of_states_to_calculate);
        assert(beta.n_cols >= requested_numer_of_states_to_calculate);
        assert(beta.n_rows == hamiltonian->get_domain()->size());
        energies = energies.rows(arma::span(0, requested_numer_of_states_to_calculate - 1));
        beta = beta.cols(arma::span(0, requested_numer_of_states_to_calculate - 1));
        // ------------------------------
        const EigResult result = {hamiltonian, success, eig_names, energies, beta};
        return result;     
    }

}
