#ifndef ONERUT_PARSER_RULES_FUNCTION_FACTORY_NORMAL_OPERATORS
#define ONERUT_PARSER_RULES_FUNCTION_FACTORY_NORMAL_OPERATORS

#include<onerut_parser_rules/function_factory_abstract.hpp>

namespace onerut_parser_rules {

    // -------------

    class CreateNormalOperatorCustomDomainFunctionFactory : public AbstractFunctionFactory {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(const std::vector<onerut_parser_exec::Asset>& argv) const override;
    };

    class CreateNormalOperatorDomainStateIndexFunctionFactory : public NaryFunctionFactory<2> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> argv) const override;
    };

    class NormalOperatorZeroFunctionFactory : public NaryFunctionFactory<1> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    class NormalOperatorHopFunctionFactory : public NaryFunctionFactory<3> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 3> args_asset) const override;
    };

    class NormalOperatorDiagFunctionFactory : public NaryFunctionFactory<2> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const override;
    };

    class NormalOperatorEyeFunctionFactory : public NaryFunctionFactory<1> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    // -------------

    class CreateOscillatorDomainFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    class CreateCreationOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    class CreateAnihilationOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    // -------------

    class CreateSpinDomainFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    class CreateSpinZetOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    class CreateSpinPlusOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    class CreateSpinMinusOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    // -------------

    class CreateEgDomainFunctionFactory : public NaryFunctionFactory<0> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 0> args_asset) const override;
    };

    class CreateSigmaXOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    class CreateSigmaZOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };
    
    // -------------    

    class CreateKronDomainFunctionFactory : public AbstractFunctionFactory {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(const std::vector<onerut_parser_exec::Asset>& argv) const override;
    };

    class CreateNormalOperatorKronPlaceholdersFunctionFactory : public AbstractFunctionFactory {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(const std::vector<onerut_parser_exec::Asset>& argv) const override;
    };

    class CreateNormalOperatorAtOperatorFunctionFactory : public NaryFunctionFactory<2> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const override;
    };

    // -------------

    class NormalOperatorEigDenseFunctionFactory : public NaryFunctionFactory<1> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    class NormalOperatorEigSparseFunctionFactory : public NaryFunctionFactory<2> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const override;
    };
    
    class NormalOperatorMeanInEigenStateFunctionFactory : public NaryFunctionFactory<3> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 3> args_asset) const override;
    };

    class NormalOperatorMeanThermalFunctionFactory : public NaryFunctionFactory<3> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 3> args_asset) const override;
    };

}

#endif