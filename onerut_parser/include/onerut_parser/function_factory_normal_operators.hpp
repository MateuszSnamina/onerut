#ifndef ONERUT_PARSER_FUNCTION_FACTORY_NORMAL_OPERATORS
#define ONERUT_PARSER_FUNCTION_FACTORY_NORMAL_OPERATORS

#include<onerut_parser/function_factory_abstract.hpp>


namespace onerut_parser {

    // -------------

    class CreateNormalDomainFunctionFactory : public AbstractFunctionFactory {
        virtual Asset make_function_otherwise_make_error(const std::vector<Asset>& argv) const override;
    };

    class NormalOperatorZeroFunctionFactory : public NaryFunctionFactory<1> {
        Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    class NormalOperatorHopFunctionFactory : public NaryFunctionFactory<3> {
        Asset make_function_otherwise_make_error(std::array<Asset, 3> args_asset) const override;
    };

    class NormalOperatorDiagFunctionFactory : public NaryFunctionFactory<2> {
        Asset make_function_otherwise_make_error(std::array<Asset, 2> args_asset) const override;
    };

    // -------------

    class CreateOscilatorDomainFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    class CreateCreationOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };
    
    class CreateAnihilationOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };
        
    // -------------

    class NormalOperatorPrintFunctionFactory : public NaryFunctionFactory<1> {
        Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

}

#endif
