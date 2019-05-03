#ifndef ONERUT_NORMAL_OPERATOR_MEAN
#define ONERUT_NORMAL_OPERATOR_MEAN

#include<memory>
#include<armadillo>

#include<onerut_scalar/scalar_real.hpp>
#include<onerut_scalar/scalar_integer.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/eig.hpp>

namespace onerut_normal_operator {

    // *************************************************************************
    // *************  Mean  ****************************************************
    // *************************************************************************

    class Mean : public onerut_scalar::Real {
    public:
        Mean(std::shared_ptr<const AbstractRealOperator> op,
                std::shared_ptr<const Eig> eig);
        double value_real() const final;
        std::vector<std::shared_ptr<const onerut_scalar::Complex>> dependency() const final;
        virtual void latch();
        virtual void reset();
        const std::shared_ptr<const AbstractRealOperator> op;
        const std::shared_ptr<const Eig> eig;

    private:
        virtual double _value_real() const = 0;
        std::optional<double> cached_result;
    };

    // -------------------------------------------------------------------------

    class MeanInEigenState : public Mean {
    public:
        MeanInEigenState(
                std::shared_ptr<const AbstractRealOperator> op,
                std::shared_ptr<const Eig> eig,
                uint32_t eigen_state);
        const uint32_t eigen_state;
    private:
        double _value_real() const final;
    };

    // -------------------------------------------------------------------------

    class MeanThermal : public Mean {
    public:
        MeanThermal(std::shared_ptr<const AbstractRealOperator> op,
                std::shared_ptr<const Eig> eig,
                double temperature);
        double temperature;
    private:
        double _value_real() const final;
    };

}

#endif