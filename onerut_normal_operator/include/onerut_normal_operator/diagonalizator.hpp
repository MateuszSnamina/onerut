#ifndef ONERUT_NORMAL_OPERATOR_DIAGONALIZATOR
#define ONERUT_NORMAL_OPERATOR_DIAGONALIZATOR

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
        const std::shared_ptr<const AbstractOperator> hamiltonian;
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
        Eig(std::shared_ptr<const AbstractOperator> hamiltonian);
        virtual EigResult value() const;
        virtual void latch();
        virtual void reset();
        std::shared_ptr<const AbstractOperator> hamiltonian;
    private:
        virtual EigResult _value() const = 0;
        std::optional<EigResult> cached_result;
    };

    // -------------------------------------------------------------------------

    class EigDense : public Eig {
    public:
        EigDense(std::shared_ptr<const AbstractOperator> hamiltonian);
    private:
        EigResult _value() const override;
    };

    // -------------------------------------------------------------------------

    class EigSparse : public Eig {
    public:
        EigSparse(std::shared_ptr<const AbstractOperator> hamiltonian,
                std::shared_ptr<const onerut_scalar::Integer> numer_of_states_to_calculate);
        std::shared_ptr<const onerut_scalar::Integer> numer_of_states_to_calculate;
    private:
        EigResult _value() const override;
    };

    // *************************************************************************
    // *************  Mean  ****************************************************
    // *************************************************************************

    class Mean : public onerut_scalar::Real {
    public:
        Mean(std::shared_ptr<const Eig> eig,
                std::shared_ptr<const AbstractOperator> op);
        double value_real() const override;
        virtual void latch();
        virtual void reset();
        const std::shared_ptr<const Eig> eig;
        const std::shared_ptr<const AbstractOperator> op;
    private:
        virtual double _value_real() const = 0;
        std::optional<double> cached_result;
    };

    // -------------------------------------------------------------------------

    class MeanInEigenState : public Mean {
    public:
        MeanInEigenState(std::shared_ptr<const Eig> eig,
                std::shared_ptr<const AbstractOperator> op,
                std::shared_ptr<const onerut_scalar::Integer> eigen_state);
        const std::shared_ptr<const onerut_scalar::Integer> eigen_state;
    private:
        double _value_real() const;
    };

    // -------------------------------------------------------------------------

    class MeanThermal : public Mean {
    public:
        MeanThermal(std::shared_ptr<const Eig> eig,
                std::shared_ptr<const AbstractOperator> op,
                std::shared_ptr<const onerut_scalar::Real> temperature);
        const std::shared_ptr<const onerut_scalar::Real> temperature;
    private:
        double _value_real() const;
    };

}

#endif