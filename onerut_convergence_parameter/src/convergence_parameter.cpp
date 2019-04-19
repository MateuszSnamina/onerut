#include<cmath>
#include<limits>

#include<onerut_convergence_parameter/convergence_parameter.hpp>

namespace {
    const double quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

namespace onerut_convergence_parameter {

    ConvergenceParameter::ConvergenceParameter(double init_value) :
    _exposed_value(init_value),
    _expression(nullptr),
    _history({init_value}),
    _threshold(1e-6) {
    }

    double ConvergenceParameter::value_real() const {
        return _exposed_value;
    }

    double ConvergenceParameter::recalcuate() {
        const double calculated_value =
                (_expression ? _expression->value_real() : quiet_nan);
        _history.push_back(calculated_value);
        return calculated_value;
    }

    void ConvergenceParameter::revolve() {
        _exposed_value = _history.back();
    }

    std::shared_ptr<onerut_scalar::Real> ConvergenceParameter::set_expression(std::shared_ptr<onerut_scalar::Real> new_expression) {
        const auto old_expression = _expression;
        _expression = new_expression;
        return old_expression;
    }

    std::shared_ptr<onerut_scalar::Real> ConvergenceParameter::expression() const {
        return _expression;
    }

    const std::vector<double> & ConvergenceParameter::history() const {
        return _history;
    }

    unsigned ConvergenceParameter::history_size() const {
        return _history.size();
    }

    std::optional<double> ConvergenceParameter::delta_or_empty() const {
        if (_history.size() <= 1)
            return std::nullopt;
        return _history.back() - _history[history_size() - 2];
    }

    double ConvergenceParameter::delta_or_nan() const {
        if (_history.size() <= 1)
            return quiet_nan;
        return _history.back() - _history[history_size() - 2];
    }

    double ConvergenceParameter::set_threshold(double new_threshold) {
        const double old_threshold = _threshold;
        _threshold = new_threshold;
        return old_threshold;
    }

    double ConvergenceParameter::threshold() const {
        return _threshold;
    }

    bool ConvergenceParameter::is_converged() const {
        return std::abs(delta_or_nan()) <= _threshold;
    }

}