#include<cstdlib>
#include<stdexcept>
#include<iostream>

#include<onerut_env/env.hpp>

namespace {
    const double quiet_nan = std::numeric_limits<double>::quiet_NaN();

    class OnlyPrefixOfTheValueIsADoubleNumber : public std::runtime_error {
    public:
        OnlyPrefixOfTheValueIsADoubleNumber();
    };

    OnlyPrefixOfTheValueIsADoubleNumber::OnlyPrefixOfTheValueIsADoubleNumber() :
    std::runtime_error("only prefix of the value is a double number") {

    }

}



namespace onerut_env {

    Env::Env(const std::string& env_variable_name, double default_value) :
    _env_variable_name(env_variable_name),
    _default_value(default_value),
    _value(std::nullopt) {
    }

    void Env::init() const {
        if (const char* env_cstr = std::getenv(_env_variable_name.c_str())) {
            const std::string env_str{env_cstr};
            std::cout << "[ENV] [INFO]"
                    << " " << "Successfully read the env-variable: '" << _env_variable_name << "'"
                    << " " << "(its value: " << "'" << env_str << "')" << std::endl;
            std::size_t pos;
            try {
                _value = std::stod(env_str, &pos); //May throw std::invalid_argument or std::out_of_range.
                if (pos == env_str.size()) {
                    std::cout << "[ENV] [INFO]"
                            << " " << "Success in converting the env - variable value into a double number."
                            << " " << "The value is: " << *_value << "."
                            << std::endl;
                } else {
                    throw OnlyPrefixOfTheValueIsADoubleNumber();
                }
            } catch (const std::exception& e) {
                std::cout << "[ENV] [ERROR]"
                        << " " << "Fail to convert the env-variable value into a double number."
                        << " " << "The quite NaN value will be used instead.";
                if (dynamic_cast<const std::invalid_argument*> (&e)) {
                    std::cout << " " << "// Error: invalid_argument.";
                } else if (dynamic_cast<const std::out_of_range*> (&e)) {
                    std::cout << " " << "// Error: out_of_range.";
                } else {
                    std::cout << " " << "// Error message: " << e.what() << ".";
                }
                std::cout << std::endl;
                _value = quiet_nan;
            }
        } else {
            std::cout << "[ENV] [INFO] The env-variable: '" << _env_variable_name << "' is not set." << std::endl;
            _value = _default_value;
            std::cout << "[ENV] [INFO] The default value: " << *_value << " will be used." << std::endl;
        }
    }

    double Env::value_real() const {
        if (!_value) {
            init();
        }
        return *_value;
    }

    const std::string& Env::env_variable_name() const {
        return _env_variable_name;
    }

}