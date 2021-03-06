#ifndef ONERUT_PARSER_RULES_FUNCTION_FACTORY_CONSTANTS
#define ONERUT_PARSER_RULES_FUNCTION_FACTORY_CONSTANTS

#include<onerut_scalar/scalar_real.hpp>
#include<onerut_scalar/scalar_complex.hpp>
#include<onerut_parser_rules/function_factory_abstract.hpp>

namespace onerut_parser_rules {

    class RealConstantFunctionFactory : public NaryFunctionFactory<0> {
    public:
        RealConstantFunctionFactory(double);
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 0>) const override;
    private:
        double value;
    };    
    
    class ComplexConstantFunctionFactory : public NaryFunctionFactory<0> {
    public:
        ComplexConstantFunctionFactory(std::complex<double>);
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 0>) const override;
    private:
        std::complex<double> value;
    };
}

#endif
