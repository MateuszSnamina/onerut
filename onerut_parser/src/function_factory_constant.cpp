#include<onerut_parser/function_factory_constant.hpp>
#include<onerut_scalar/scalar_real.hpp>
#include<onerut_scalar/scalar_complex.hpp>

using namespace std::complex_literals;
const double pi = 3.14159265358979323846;
const double e = 2.71828182845904523536;


namespace onerut_parser {

    CompileResult
    PiConstantFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 0>) const {
        return CompileResult::from_value<onerut_scalar::Real>(
                std::make_shared<onerut_scalar::LitReal>(pi));
    }

    CompileResult
    EulerConstantFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 0>) const {
        return CompileResult::from_value<onerut_scalar::Real>(
                std::make_shared<onerut_scalar::LitReal>(e));
    }

    CompileResult
    ImaginaryUnitFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 0>) const {
        return CompileResult::from_value<onerut_scalar::Complex>(
                std::make_shared<onerut_scalar::LitComplex>(1i));
    }

}
