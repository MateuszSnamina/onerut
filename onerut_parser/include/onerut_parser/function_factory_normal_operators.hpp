#ifndef ONERUT_PARSER_FUNCTION_FACTORY_NORMAL_OPERATORS
#define ONERUT_PARSER_FUNCTION_FACTORY_NORMAL_OPERATORS

#include<onerut_parser/function_factory_abstract.hpp>

namespace onerut_parser {

    class NormalOperatorZerosFunctionFactory : public NaryFunctionFactory<0> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 0> args_compile_result) const override;
    };

    class NormalOperatorDiagFunctionFactory : public NaryFunctionFactory<2> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 2> args_compile_result) const override;
    };

    class NormalOperatorHopFunctionFactory : public NaryFunctionFactory<3> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 3> args_compile_result) const override;
    };

    class NormalOperatorPrintFactory : public NaryFunctionFactory<2> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 2> args_compile_result) const override;
    };

}

#endif
