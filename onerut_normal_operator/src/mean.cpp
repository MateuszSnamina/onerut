#include<cassert>
#include<algorithm>
#include<iterator>
#include<boost/cast.hpp>

#include<onerut_normal_operator/calculate_mean.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>

namespace onerut_normal_operator {

    // *************************************************************************
    // *************  Mean  ****************************************************
    // *************************************************************************

    Mean::Mean(
            std::shared_ptr<const AbstractRealOperator> op,
            std::shared_ptr<const Eig> eig) :
    op(op),
    eig(eig),
    cached_result(std::nullopt) {
        assert(op);
        assert(eig);
        assert(eig->hamiltonian);
        assert(are_the_same_domains(*op->get_domain(), *eig->hamiltonian->get_domain()));
    }

    double Mean::value_real() const {
        return ( cached_result ? *cached_result : _value_real());
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> Mean::dependence() const {
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> result;
        result.push_back(op);
        result.push_back(eig);
        return result;
    }

    void Mean::latch() {
        cached_result = _value_real();
    }

    void Mean::reset() {
        cached_result = std::nullopt;
    }

    // *************************************************************************

    MeanInEigenState::MeanInEigenState(
            std::shared_ptr<const AbstractRealOperator> op,
            std::shared_ptr<const Eig> eig,
            uint32_t eigen_state) :
    Mean(op, eig),
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

    MeanThermal::MeanThermal(
            std::shared_ptr<const AbstractRealOperator> op,
            std::shared_ptr<const Eig> eig,
            double temperature) :
    Mean(op, eig),
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
