#include<cassert>
#include<vector> 
#include<string> 
#include<boost/cast.hpp>

#include<log_utils/fancy_log_mat.hpp> 
#include<onerut_normal_operator/to_mat.hpp> 
#include<onerut_normal_operator/calculate_mean.hpp>
#include<onerut_normal_operator/diagonalizator.hpp>

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
        assert(0); // TODO implement
        // ------------------------------
        const auto requested_numer_of_states_to_calculate =
                boost::numeric_cast<arma::uword>(numer_of_states_to_calculate->value_integer());
        const auto space_dim =
                boost::numeric_cast<arma::uword>(hamiltonian->get_domain()->size());
        // ---------------------------------------------------------------------
        const std::vector<std::string> eig_names = _eig_names(hamiltonian->get_domain()->size());
        // ------------------------------
        arma::vec energies;
        arma::mat beta;
        // ------------------------------
        const arma::sp_mat hamiltonian_sp_mat /*= to_sp_mat(*hamiltonian, requested_numer_of_states_to_calculate)*/;
        bool success = arma::eigs_sym(energies, beta, hamiltonian_sp_mat,
                requested_numer_of_states_to_calculate, "sa");
        // ------------------------------
        if (!success) { // Arma reports en error.
            std::cout << "[INFO   ] [SPARSE] Armadillo failed to diagonalize the hamiltonian!" << std::endl;
            if (hamiltonian_sp_mat.n_rows < 100) {
                // Fall-back -> use dense calculation for small matrices.
                std::cout << "[INFO   ] [SPARSE] [FALL-BACK] Armadillo failed to diagonalize the hamiltonian as a dense matrix!";
                // ... TODO
            } else {
                // Give up -- return success = false;
            }
        } else { // Arma does not report en error.
            if (energies.n_elem < requested_numer_of_states_to_calculate) {
                // Fall-back -> increase requested_numer_of_states_to_calculate.                
                // ... TODO
                std::cout << "[INFO   ] [SPARSE] Armadillo failed to diagonalize the hamiltonian but not reported an error!" << std::endl;
                std::cout << "[INFO   ] [SPARSE] [FALL-BACK] The program is about to try diagonalize the hamiltonian with grater n_calculated_states requested." << std::endl;
                const auto second_try_requested_numer_of_states_to_calculate =
                        std::min(requested_numer_of_states_to_calculate + 3, space_dim - 1);
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
        // ------------------------------
        //    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        //    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        //    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        // https://github.com/MateuszSnamina/stars-ring/blob/master/starsring_app/stars_ring_numerical/src/standard_calculator.cpp
        //         
        //        if (!arma::eigs_sym(_energies, _states, _hamiltonian_sparse,
        //                      _n_calculated_states, "sa")) {
        //    if (_hamiltonian_sparse.n_rows < 100) {
        //      std::cout << "[INFO   ] [SPARSE] Armadillo failed to diagonalize the "
        //                   "hamiltonian!"
        //                << std::endl;
        //      std::cout << "[INFO   ] [SPARSE] [FALL-BACK DENSE] Armadillo failed to "
        //                   "diagonalize the "
        //                   "hamiltonian as a dense matrix!"
        //                << std::endl;
        //      if (!arma::eig_sym(_energies, _states, arma::mat(_hamiltonian_sparse))) {
        //        std::cerr << "[ERROR  ] [SPARSE] [FALL-BACK DENSE] Armadillo failed to "
        //                     "diagonalize the hamiltonian!"
        //                  << std::endl;
        //        std::cerr << "[ERROR  ] [SPARSE] [FALL-BACK DENSE] Program termination "
        //                     "(with exit code 20)."
        //                  << std::endl;
        //        exit(20);
        //      }
        //    } else {
        //      std::cerr << "[ERROR  ] [SPARSE] Armadillo failed to diagonalize the "
        //                   "hamiltonian!"
        //                << std::endl;
        //      std::cerr << "[ERROR  ] [SPARSE] Program termination (with exit code 20)."
        //                << std::endl;
        //      exit(20);
        //    }
        //  }
        //  if (_energies.n_elem < _n_calculated_states) {
        //    std::cout
        //        << "[INFO   ] [SPARSE] Armadillo failed to diagonalize the hamiltonian "
        //           "but not reporter an error!"
        //        << std::endl;
        //    std::cout << "[INFO   ] [SPARSE] [SECOND-TRY] The program is about to try "
        //                 "diagonalize the "
        //                 "hamiltonian with grater n_calculated_states requested."
        //              << std::endl;
        //    const unsigned n_calculated_states_second_try = std::min(
        //        _n_calculated_states + 3, _basis_box.localized_basis().size() - 1);
        //    std::cout << "[INFO   ] [SECOND-TRY] n_calculated_states, "
        //                 "n_calculated_states_second_try: "
        //              << _n_calculated_states << ", " << n_calculated_states_second_try
        //              << "." << std::endl;
        //    if (!arma::eigs_sym(_energies, _states, _hamiltonian_sparse,
        //                        n_calculated_states_second_try, "sa")) {
        //      std::cerr << "[ERROR  ] [SECOND-TRY] Armadillo failed to diagonalize the "
        //                   "hamiltonian!"
        //                << std::endl;
        //      std::cerr
        //          << "[ERROR  ] [SECOND-TRY] Program termination (with exit code 20)."
        //          << std::endl;
        //      exit(20);
        //    }
        //  }
        //  assert(_energies.n_elem == _states.n_cols);
        //  assert(_energies.n_elem >= _n_calculated_states);
        //  assert(_states.n_cols >= _n_calculated_states);
        //  assert(_states.n_rows == _hamiltonian_sparse.n_rows);
        //  _energies = _energies.rows(arma::span(0, _n_calculated_states - 1));
        //_states = _states.cols(arma::span(0, _n_calculated_states - 1)); 
        //         
        //         
    }

    // *************************************************************************
    // *************  Mean  ****************************************************
    // *************************************************************************

    Mean::Mean(std::shared_ptr<const Eig> eig,
            std::shared_ptr<const AbstractOperator> op) :
    eig(eig),
    op(op),
    cached_result(std::nullopt) {
        assert(eig);
        assert(op);
    }

    double Mean::value_real() const {
        return ( cached_result ? *cached_result : _value_real());
    }

    void Mean::latch() {
        cached_result = _value_real();
    }

    void Mean::reset() {
        cached_result = std::nullopt;
    }

    // *************************************************************************

    MeanInEigenState::MeanInEigenState(std::shared_ptr<const Eig> eig,
            std::shared_ptr<const AbstractOperator> op,
            std::shared_ptr<const onerut_scalar::Integer> eigen_state) :
    Mean(eig, op),
    eigen_state(eigen_state) {
        assert(eigen_state);
    }

    double MeanInEigenState::_value_real() const {
        const EigResult eig_results = eig->value();
        if (!op)
            return arma::datum::nan;
        const auto eig_number = eigen_state->value_integer();
        if (boost::numeric_cast<arma::uword>(eig_number) >= eig_results.beta.n_cols)
            return arma::datum::nan;
        return onerut_normal_operator::calculate_mean(*op, eig_results.beta.col(eig_number));
    }

    // *************************************************************************

    MeanThermal::MeanThermal(std::shared_ptr<const Eig> eig,
            std::shared_ptr<const AbstractOperator> op,
            std::shared_ptr<const onerut_scalar::Real> temperature) :
    Mean(eig, op),
    temperature(temperature) {
        assert(temperature);
    }

    double MeanThermal::_value_real() const {
        assert(0); // TODO implement
        //        const EigResult eig_results = eig->value();
        //        if (!op)
        //            return arma::datum::nan;
        //        const auto eig_number = eigen_state->value_integer();
        //        // TODO handle negative
        //        if (eig_number >= eig_results.beta.n_cols)// TODO fix comparison incompatibility
        //            return arma::datum::nan;
        //        return onerut_normal_operator::calculate_mean(*op, eig_results.beta.col(eig_number));
    }

}
