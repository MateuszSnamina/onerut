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

    void EigsResult::print_energies(std::ostream& stream, unsigned chunk_size, std::string line_prefix) const {
        fancy_logging::log(stream,{"Energy"}, eig_names,
                arma::trans(energies),
                chunk_size, line_prefix);
    }

    void EigsResult::print_beta(std::ostream& stream, unsigned chunk_size, std::string line_prefix) const {
        fancy_logging::log(stream, hamiltonian->get_domain()->state_names, eig_names,
                beta,
                chunk_size, line_prefix);
    }

    void EigsResult::log(std::ostream& stream, std::string line_prefix) const {
        auto flags = stream.flags();
        stream << std::scientific << std::showpos;
        stream.width(10);
        const unsigned log_chunk_size = 5;
        print_energies(stream, log_chunk_size, line_prefix);
        print_beta(stream, log_chunk_size, line_prefix);
        stream.width(0);
        stream.flags(flags);
    }

    // ******************************

    Eigs::Eigs(std::shared_ptr<const AbstractOperator> hamiltonian) :
    hamiltonian(hamiltonian) {
        assert(hamiltonian);
    }

    EigsResult Eigs::_diag(std::ostream& stream, std::string line_prefix) const {
        // ---------------------------------------------------------------------
        stream << line_prefix << "[progress] About to diagonalize." << std::endl;
        // ---------------------------------------------------------------------
        const std::vector<std::string> eig_names = _eig_names(hamiltonian->get_domain()->size());
        // ---------------------------------------------------------------------
        arma::vec energies;
        arma::mat beta;
        const arma::mat hamiltonian_mat = to_mat(*hamiltonian);
        const bool success = arma::eig_sym(energies, beta, hamiltonian_mat);
        if (!success) {
            stream << line_prefix << "[progress] Fail to diagonalize." << std::endl;
        }
        // ---------------------------------------------------------------------
        stream << line_prefix << "[progress] Has successfully diagonalized." << std::endl;
        // ---------------------------------------------------------------------
        const EigsResult result = {hamiltonian, success, eig_names, energies, beta};
        return result;
    }

    EigsResult Eigs::diag(std::ostream& stream, std::string line_prefix) const {
        return ( cached_result ?
                *cached_result :
                _diag(stream, line_prefix));
    }

    void Eigs::exec(std::ostream& stream, std::string line_prefix) {
        cached_result.emplace(_diag(stream, line_prefix));
    }

    void Eigs::free(std::ostream& stream, std::string line_prefix) {
        cached_result = std::nullopt;
    }

    // ******************************

    Mean::Mean(std::shared_ptr<const Eigs> eigs,
            std::shared_ptr<const AbstractOperator> op,
            std::shared_ptr<const onerut_scalar::Integer> eigen_state) :
    eigs(eigs),
    op(op),
    eigen_state(eigen_state) {
        assert(eigs);
        assert(op);
        assert(eigs);
    }

    double Mean::_value_real(std::ostream& stream, std::string line_prefix) const {
        const EigsResult eig_results = eigs->diag(stream, line_prefix);
        if (!op)
            return arma::datum::nan;
        //if (!state_index)
        //    return arma::datum::nan;
        //if (are_the_same_domains(*op->get_domain(), *state_index->domain))
        //    return arma::datum::nan;
        const auto eig_number = eigen_state->value_integer();
        // TODO handle negative
        if (eig_number >= eig_results.beta.n_cols)// TODO fix comparison incompatibility
            return arma::datum::nan;
        return onerut_normal_operator::calculate_mean(*op, eig_results.beta.col(eig_number));
    }

    double Mean::value_real() const {
        return ( cached_result ?
                *cached_result :
                _value_real(std::cout, "xxxxxx"));
    }

    void Mean::exec(std::ostream& stream, std::string line_prefix) {
        cached_result = _value_real(stream, line_prefix);
    }

    void Mean::free(std::ostream& stream, std::string line_prefix) {
        cached_result = std::nullopt;
    }


}
