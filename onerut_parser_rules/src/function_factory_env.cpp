#include<onerut_env/env.hpp>
#include<onerut_parser_exec/asset_ref_container.hpp>
#include<onerut_parser_exec/asset_utility.hpp>
#include<onerut_parser_rules/asset_utility_concrete.hpp>
#include<onerut_parser_rules/function_factory_env.hpp>

namespace onerut_parser_rules {

    onerut_parser_exec::Asset
    BindToEnvFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!onerut_parser_exec::utility::is_unset_ref(args_asset[0]))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_real_or_integer(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const std::string env_variable_name = onerut_parser_exec::utility::name_of_unset_ref(args_asset[0]);
        const auto default_value = utility::to_real(arg1_asset_deref);
        const double default_value_buildin = default_value->value_real();
        // ---------------------------------------------------------------------
        using EnvT = onerut_env::Env;
        const auto env = std::make_shared<EnvT>(env_variable_name, default_value_buildin);
        const auto env_asset_deref = onerut_parser_exec::AssetDeref::from_value<EnvT>(env);
        const auto env_asset_ref = std::make_shared<onerut_parser_exec::AssetConstRef>(env_variable_name, env_asset_deref);
        if (!onerut_parser_exec::AssetRefContainer::global_instance().put(env_asset_ref)) {
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::IllegalSecondAssignError>());
        }
        // ---------------------------------------------------------------------
        env->value_real(); // force the env object initialization (side effect: print some info on stdout)
        // ---------------------------------------------------------------------
        return onerut_parser_exec::Asset::from_reference(env_asset_ref);
        return args_asset[0];
    }

}