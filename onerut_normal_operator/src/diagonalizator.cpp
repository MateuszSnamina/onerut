#include<cassert>
#include<vector> 
#include<string> 

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
        //        // ---------------------------------------------------------------------
        //        const std::vector<std::string> eig_names = _eig_names(hamiltonian->get_domain()->size());
        //        // ---------------------------------------------------------------------
        //        arma::vec energies;
        //        arma::mat beta;
        //        const arma::mat hamiltonian_mat = to_mat(*hamiltonian);
        //        const bool success = arma::eig_sym(energies, beta, hamiltonian_mat);
        //        // ---------------------------------------------------------------------
        //        const EigResult result = {hamiltonian, success, eig_names, energies, beta};
        //        return result;
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
        // TODO handle negative
        if (eig_number >= eig_results.beta.n_cols)// TODO fix comparison incompatibility
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
