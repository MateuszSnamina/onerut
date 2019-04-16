#include<onerut_scalar/scalar_real.hpp>
#include<onerut_scalar/scalar_complex.hpp>
#include<onerut_parser_rules/function_factory_constant.hpp>

namespace onerut_parser {

    RealConstantFunctionFactory::RealConstantFunctionFactory(double value) :
    value(value) {
    }

    Asset
    RealConstantFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 0>) const {
        return Asset::from_value<onerut_scalar::Real>(
                std::make_shared<onerut_scalar::LitReal>(value));
    }

    ComplexConstantFunctionFactory::ComplexConstantFunctionFactory(std::complex<double> value) :
    value(value) {
    }

    Asset
    ComplexConstantFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 0>) const {
        return Asset::from_value<onerut_scalar::Complex>(
                std::make_shared<onerut_scalar::LitComplex>(value));
    }

}
