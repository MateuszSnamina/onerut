#include<onerut_parser/asset_utility.hpp>
#include<onerut_parser/function_factory_normal_operators.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_zero.hpp>
#include<onerut_normal_operator/to_mat.hpp>

#include<iostream>//debug TODO delete
namespace onerut_parser {

    Asset
    NormalOperatorZeroFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_normal_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto domain = utility::to_normal_operator_domain(arg0_asset_deref);       
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::ZeroOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(domain));
    }

    Asset
    NormalOperatorDiagFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_real_or_integer(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg1_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto value = utility::to_real(arg0_asset_deref);
        const auto site = utility::to_normal_operator_state_index(arg1_asset_deref);
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::DiagOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(value, site));
    }

    Asset
    NormalOperatorHopFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 3> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        const auto & arg2_asset_deref = args_asset[2].deref();
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!arg2_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_real_or_integer(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg1_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg2_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto value = utility::to_real(arg0_asset_deref);
        const auto site1 = utility::to_normal_operator_state_index(arg1_asset_deref);
        const auto site2 = utility::to_normal_operator_state_index(arg2_asset_deref);
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::HopOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(value, site1, site2)
                );
    }

    Asset CreateNormalDomainFunctionFactory::make_function_otherwise_make_error(const std::vector<Asset>& argv) const {
        const auto argc = argv.size();
        for (unsigned index = 0; index < argc; ++index)
            if (!utility::is_unset_ref(argv[index]))
                return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // Take out state names:
        std::vector<std::string> state_names;
        state_names.reserve(argc);
        for (unsigned index = 0; index < argc; ++index)
            state_names.push_back(utility::name_of_unset_ref(argv[index]));
        // Make domain object:
        auto domain = std::make_shared<onerut_normal_operator::Domain>(state_names);
        auto domain_asset = Asset::from_value<onerut_normal_operator::Domain>(domain);
        // Make state-index objects:
        for (unsigned index = 0; index < argc; ++index) {
            const std::string name = domain->state_names[index];
            const auto state_asset_deref = AssetDeref::from_value<onerut_normal_operator::StateIndex>(domain->crate_state(index));
            const auto state_ref = std::make_shared<AssetConstRef>(name, state_asset_deref);
            if (!GlobalIdentifiers::instance().put(name, state_ref)) {
                return Asset::from_compile_error(std::make_shared<IllegalSecondAssignError>());
            }
        }
        // Return domain compile result.
        return domain_asset;
    }

    Asset NormalOperatorPrintFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_normal_operator(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto normal_operator = utility::to_normal_operator(arg0_asset_deref);
        const arma::mat M = onerut_normal_operator::to_mat(*normal_operator);
        std::cout << "Normal operator:" << std::endl;
        std::cout << M << std::endl;
        return args_asset[0];
    }

}
