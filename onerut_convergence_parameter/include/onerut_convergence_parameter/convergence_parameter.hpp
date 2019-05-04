#ifndef ONERUT_CONVERGENCE_PARAMETER_CONVERGENCE_PARAMETER
#define ONERUT_CONVERGENCE_PARAMETER_CONVERGENCE_PARAMETER

#include<memory>
#include<vector>
#include<optional>

#include<onerut_scalar/scalar_real.hpp>

namespace onerut_convergence_parameter {

    class ConvergenceParameter : public onerut_scalar::Real {
    public:
        ConvergenceParameter(double init_value);
        double value_real() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
        // Calculate the new value and save it in a history log,
        // but not expose as the param  value until revolve as called:
        double recalcuate();
        // Adapts the last recalculated value as
        // the value exposed via value_real():
        void revolve();
        // Expression for recalculation:
        std::shared_ptr<const onerut_scalar::Real> set_expression(std::shared_ptr<const onerut_scalar::Real> new_expression);
        std::shared_ptr<const onerut_scalar::Real> expression() const;
        // History:
        const std::vector<double> & history() const;
        unsigned history_size() const;
        std::optional<double> delta_or_empty() const;
        double delta_or_nan() const;
        // Threshold:
        double set_threshold(double new_threshold); //returns old threshold
        double threshold() const;
        bool is_converged() const;
    private:
        double _exposed_value;
        std::shared_ptr<const onerut_scalar::Real> _expression;// TODO change into weak_ptr!!!!!
        std::vector<double> _history;
        double _threshold;
    };

}

#endif