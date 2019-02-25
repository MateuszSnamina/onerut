#ifndef ONERUT_PARSER_FUNCTION_FACTORY_NORMAL_OPERATORS
#define ONERUT_PARSER_FUNCTION_FACTORY_NORMAL_OPERATORS

#include<onerut_parser/diag_request.hpp>
#include<onerut_parser/function_factory_abstract.hpp>

namespace onerut_parser {

    // -------------

    class CreateNormalDomainFunctionFactory : public AbstractFunctionFactory {
        virtual Asset make_function_otherwise_make_error(const std::vector<Asset>& argv) const override;
    };

    class CreateNormalDomainStateIndexFunctionFactory : public NaryFunctionFactory<2> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 2> argv) const override;
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

    class NormalOperatorEyeFunctionFactory : public NaryFunctionFactory<1> {
        Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    // -------------

    class CreateOscillatorDomainFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    class CreateCreationOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    class CreateAnihilationOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    // -------------

    class CreateSpinDomainFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    class CreateSpinZetOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    class CreateSpinPlusOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    class CreateSpinMinusOperatorFunctionFactory : public NaryFunctionFactory<1> {
        virtual Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    // -------------

    // diag request to another file.//TODO delete

    /*
    struct DiagRequest : public AssetDeref {
        DiagRequest(std::shared_ptr<const onerut_normal_operator::AbstractOperator> hamiltonian);
        std::shared_ptr<const onerut_normal_operator::AbstractOperator> hamiltonian;
    };

    inline
    DiagRequest::DiagRequest(std::shared_ptr<const onerut_normal_operator::AbstractOperator> hamiltonian) :
    hamiltonian(hamiltonian) {
    }
     */

    class NormalOperatorDiagRequestFactory : public NaryFunctionFactory<1> {
        Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

    // -------------

    class NormalOperatorPrintFunctionFactory : public NaryFunctionFactory<1> {
        Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };


}

#endif
