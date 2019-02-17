#ifndef ONERUT_PARSER_FUNCTION_FACTORY_CONSTANTS
#define ONERUT_PARSER_FUNCTION_FACTORY_CONSTANTS

#include<onerut_parser/function_factory_abstract.hpp>
#include<onerut_scalar/scalar_real.hpp>
#include<onerut_scalar/scalar_complex.hpp>

namespace onerut_parser {

    class PiConstantFunctionFactory : public NaryFunctionFactory<0> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 0>) const override;
    };

    class EulerConstantFunctionFactory : public NaryFunctionFactory<0> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 0>) const override;
    };

    class ImaginaryUnitFunctionFactory : public NaryFunctionFactory<0> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 0>) const override;
    };

}

#endif
