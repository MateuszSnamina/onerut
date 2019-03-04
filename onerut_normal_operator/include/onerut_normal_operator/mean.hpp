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