#ifndef ONERUT_NORMAL_OPERATOR_EIG
#define ONERUT_NORMAL_OPERATOR_EIG

#include<memory>
#include<armadillo>

#include<onerut_scalar/scalar_real.hpp>
#include<onerut_scalar/scalar_integer.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    // *************************************************************************
    // *************  Eig   ****************************************************
    // *************************************************************************

    struct EigResult {
        explicit EigResult(
                const std::shared_ptr<const AbstractRealOperator> hamiltonian);
        EigResult(const std::shared_ptr<const AbstractRealOperator> hamiltonian,
                const std::vector<std::string> eig_names,
                const arma::vec energies,
                const arma::mat beta);
        const std::shared_ptr<const AbstractRealOperator> hamiltonian;
        const bool success;
        const std::vector<std::string> eig_names;
        const arma::vec energies;
        const arma::mat beta;
        void print_energies(std::ostream& stream, unsigned chunk_size = 5, std::string line_prefix = "") const;
        void print_beta(std::ostream& stream, unsigned chunk_size = 5, std::string line_prefix = "") const;
        void log(std::ostream& stream, std::string line_prefix = "") const;
    };

    // -------------------------------------------------------------------------

    class Eig {
    public:
        Eig(std::shared_ptr<const AbstractRealOperator> hamiltonian);
        virtual EigResult value() const;
        virtual void latch();
        virtual void reset();
        std::shared_ptr<const AbstractRealOperator> hamiltonian;
    private:
        virtual EigResult _value() const = 0;
        std::optional<EigResult> cached_result;
    };

    // -------------------------------------------------------------------------

    class EigDense : public Eig {
    public:
        EigDense(std::shared_ptr<const AbstractRealOperator> hamiltonian);
    private:
        EigResult _value() const override;
    };

    // -------------------------------------------------------------------------

    class EigSparse : public Eig {
    public:
        EigSparse(std::shared_ptr<const AbstractRealOperator> hamiltonian,
                uint32_t numer_of_states_to_calculate);
        uint32_t numer_of_states_to_calculate;
    private:
        EigResult _value() const override;
    };

}

#endif