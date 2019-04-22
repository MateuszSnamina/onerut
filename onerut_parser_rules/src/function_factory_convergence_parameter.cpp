#include<onerut_parser_rules/asset_utility_concrete.hpp>
#include<onerut_parser_rules/function_factory_convergence_parameter.hpp>

namespace onerut_parser_rules {

    onerut_parser_exec::Asset
    CreateConvergenceParameterFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_real_or_integer(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto initial_value = utility::to_real(arg0_asset_deref);
        const auto initial_value_buildin = initial_value->value_real();
        // ---------------------------------------------------------------------
        using ConvergenceParameterT = onerut_convergence_parameter::ConvergenceParameter;
        return onerut_parser_exec::Asset::from_value<ConvergenceParameterT>(
                std::make_shared<ConvergenceParameterT>(initial_value_buildin));
    }

    onerut_parser_exec::Asset
    ArrowFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_convergence_parameter(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_real_or_integer(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto convergence_parameter = utility::to_convergence_parameter(arg0_asset_deref);
        const auto expression = utility::to_real(arg1_asset_deref);
        // ---------------------------------------------------------------------
        convergence_parameter->set_expression(expression);
        // ---------------------------------------------------------------------
        return args_asset[0];
    }

    onerut_parser_exec::Asset
    GlueFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_convergence_parameter(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_real_or_integer(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto convergence_parameter = utility::to_convergence_parameter(arg0_asset_deref);
        const auto threshold = utility::to_real(arg1_asset_deref);
        const auto threshold_buildin = threshold->value_real();
        // ---------------------------------------------------------------------
        convergence_parameter->set_threshold(threshold_buildin);
        // ---------------------------------------------------------------------
        return args_asset[0];
    }

}
