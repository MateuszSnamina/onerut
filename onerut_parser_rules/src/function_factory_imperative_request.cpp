#include<onerut_request/request_imperative.hpp>
#include<onerut_parser_rules/asset_utility_concrete.hpp>
#include<onerut_parser_rules/function_factory_imperative_request.hpp>

namespace onerut_parser_rules {

    onerut_parser_exec::Asset LatchRequestFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------        
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------        
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        if (utility::is_normal_operator_eig(arg0_asset_deref)) {
            const auto normal_operator_eig = utility::to_normal_operator_eig(arg0_asset_deref);
            return onerut_parser_exec::Asset::from_value<onerut_request::ImperativeRequest>(
                    std::make_shared<onerut_request::LatchRequestTyped<onerut_normal_operator::Eig> >(normal_operator_eig)
                    );
        }
        // ---------------------------------------------------------------------        
        if (utility::is_normal_operator_mean(arg0_asset_deref)) {
            const auto normal_operator_mean = utility::to_normal_operator_mean(arg0_asset_deref);
            return onerut_parser_exec::Asset::from_value<onerut_request::ImperativeRequest>(
                    std::make_shared<onerut_request::LatchRequestTyped<onerut_normal_operator::Mean> >(normal_operator_mean)
                    );
        }
        // ---------------------------------------------------------------------        
        return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
    }

    onerut_parser_exec::Asset ResetRequestFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------        
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------        
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        if (utility::is_normal_operator_eig(arg0_asset_deref)) {
            const auto normal_operator_eig = utility::to_normal_operator_eig(arg0_asset_deref);
            return onerut_parser_exec::Asset::from_value<onerut_request::ImperativeRequest>(
                    std::make_shared<onerut_request::ResetRequestTyped<onerut_normal_operator::Eig> >(normal_operator_eig)
                    );
        }
        // ---------------------------------------------------------------------        
        if (utility::is_normal_operator_mean(arg0_asset_deref)) {
            const auto normal_operator_mean = utility::to_normal_operator_mean(arg0_asset_deref);
            return onerut_parser_exec::Asset::from_value<onerut_request::ImperativeRequest>(
                    std::make_shared<onerut_request::ResetRequestTyped<onerut_normal_operator::Mean> >(normal_operator_mean)
                    );
        }
        // ---------------------------------------------------------------------        
        return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
    }

}
