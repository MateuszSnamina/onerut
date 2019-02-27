#include<onerut_parser/asset_utility.hpp>
#include<onerut_parser/request_imperative.hpp>
#include<onerut_parser/function_factory_imperative_request.hpp>

namespace onerut_parser {

    Asset LatchRequestFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------        
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------        
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        if (!utility::is_normal_operator_eigs(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        const auto normal_operator_eigs = utility::to_normal_operator_eigs(arg0_asset_deref);
        // ---------------------------------------------------------------------        
        return Asset::from_value<onerut_parser::ImperativeRequest>(
                std::make_shared<onerut_parser::LatchRequestTyped<onerut_normal_operator::Eigs> >(normal_operator_eigs)
                );
    }

    Asset ResetRequestFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------        
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------        
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        if (!utility::is_normal_operator_eigs(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        const auto normal_operator_eigs = utility::to_normal_operator_eigs(arg0_asset_deref);
        // ---------------------------------------------------------------------        
        return Asset::from_value<onerut_parser::ImperativeRequest>(
                std::make_shared<onerut_parser::ResetRequestTyped<onerut_normal_operator::Eigs> >(normal_operator_eigs)
                );
    }

}
