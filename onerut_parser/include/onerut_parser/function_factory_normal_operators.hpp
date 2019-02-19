#ifndef ONERUT_PARSER_FUNCTION_FACTORY_NORMAL_OPERATORS
#define ONERUT_PARSER_FUNCTION_FACTORY_NORMAL_OPERATORS

#include<onerut_parser/function_factory_abstract.hpp>


namespace onerut_parser {

    class NormalOperatorZeroFunctionFactory : public NaryFunctionFactory<1> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 1> args_compile_result) const override;
    };

    class NormalOperatorHopFunctionFactory : public NaryFunctionFactory<3> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 3> args_compile_result) const override;
    };

    class NormalOperatorDiagFunctionFactory : public NaryFunctionFactory<2> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 2> args_compile_result) const override;
    };

    class CreateNormalDomainFunctionFactory : public AbstractFunctionFactory {
        virtual CompileResult make_function_otherwise_make_error(const std::vector<CompileResult>& argv) const override;
    };

    class NormalOperatorPrintFunctionFactory : public NaryFunctionFactory<1> {
        CompileResult make_function_otherwise_make_error(std::array<CompileResult, 1> args_compile_result) const override;
    };

}

#endif
