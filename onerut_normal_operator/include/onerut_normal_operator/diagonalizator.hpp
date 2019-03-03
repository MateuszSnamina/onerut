#ifndef ONERUT_NORMAL_OPERATOR_DIAGONALIZATOR
#define ONERUT_NORMAL_OPERATOR_DIAGONALIZATOR

#include<memory>
#include<armadillo>

#include<onerut_scalar/scalar_real.hpp>
#include<onerut_scalar/scalar_integer.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    struct EigResult {
        const std::shared_ptr<const AbstractOperator> hamiltonian;
        const bool success;
        const std::vector<std::string> eig_names;
        const arma::vec energies;
        const arma::mat beta;
        void print_energies(std::ostream& stream, unsigned chunk_size = 5, std::string line_prefix = "") const;
        void print_beta(std::ostream& stream, unsigned chunk_size = 5, std::string line_prefix = "") const;
        void log(std::ostream& stream, std::string line_prefix = "") const;
    };

    class Eig {
    public:
        Eig(std::shared_ptr<const AbstractOperator> hamiltonian);
        EigResult value() const;
        void latch();
        void reset();
    public:
        std::shared_ptr<const AbstractOperator> hamiltonian;
    private:
        EigResult _value() const;
        std::optional<EigResult> cached_result;
    };

    class Mean : public onerut_scalar::Real {
    public:
        Mean(std::shared_ptr<const Eig> eig,
                std::shared_ptr<const AbstractOperator> op,
                std::shared_ptr<const onerut_scalar::Integer> eigen_state);
        double value_real() const override;
        void latch();
        void reset();
    public:
        std::shared_ptr<const Eig> eig;
        std::shared_ptr<const AbstractOperator> op;
        std::shared_ptr<const onerut_scalar::Integer> eigen_state;
    private:
        double _value_real() const;
        std::optional<double> cached_result;
    };

}

#endif