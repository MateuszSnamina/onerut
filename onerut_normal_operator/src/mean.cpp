#include<cassert>
#include<boost/cast.hpp>

#include<onerut_normal_operator/calculate_mean.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>

namespace onerut_normal_operator {

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
            uint32_t eigen_state) :
    Mean(eig, op),
    eigen_state(eigen_state) {
    }

    double MeanInEigenState::_value_real() const {
        const EigResult eig_results = eig->value();
        if (!op)
            return arma::datum::nan;
        return onerut_normal_operator::calculate_mean(
                *op, eig_results.beta.col(eigen_state));
    }

    // *************************************************************************

    MeanThermal::MeanThermal(std::shared_ptr<const Eig> eig,
            std::shared_ptr<const AbstractOperator> op,
            double temperature) :
    Mean(eig, op),
    temperature(temperature) {
    }

    double MeanThermal::_value_real() const {
        const EigResult eig_results = eig->value();
        if (!op)
            return arma::datum::nan;
        return calculate_thermal_mean(
                *op, eig_results.beta,
                eig_results.energies, temperature);
    }

}
