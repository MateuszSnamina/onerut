#include<onerut_parser/function_factory_constant.hpp>
#include<onerut_scalar/scalar_real.hpp>
#include<onerut_scalar/scalar_complex.hpp>

namespace onerut_parser {

    RealConstantFunctionFactory::RealConstantFunctionFactory(double value) :
    value(value) {
    }

    CompileResult
    RealConstantFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 0>) const {
        return CompileResult::from_value<onerut_scalar::Real>(
                std::make_shared<onerut_scalar::LitReal>(value));
    }

    ComplexConstantFunctionFactory::ComplexConstantFunctionFactory(std::complex<double> value) :
    value(value) {
    }

    CompileResult
    ComplexConstantFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 0>) const {
        return CompileResult::from_value<onerut_scalar::Complex>(
                std::make_shared<onerut_scalar::LitComplex>(value));
    }

}
