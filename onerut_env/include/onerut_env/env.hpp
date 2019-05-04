#ifndef ONERUT_ENV_ENV
#define ONERUT_ENV_ENV

#include<string>
#include<optional>

#include<onerut_scalar/scalar_real.hpp>

namespace onerut_env {

    class Env : public onerut_scalar::Real {
    public:
        Env(const std::string& env_variable_name, double default_value);
        double value_real() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
        const std::string& env_variable_name() const;
    private:
        void init() const; //const but change the mutable cache
        const std::string _env_variable_name;
        const double _default_value;
        mutable std::optional<double> _value;
    };

}

#endif