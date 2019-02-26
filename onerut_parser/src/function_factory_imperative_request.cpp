#include<boost/cast.hpp>

//#include<onerut_parser/asset_utility.hpp>
//#include<onerut_parser/function_factory_normal_operators.hpp>
//#include<onerut_parser/imperative_request.hpp>
//#include<onerut_parser/asset_ref_container.hpp> //TODO remove??
//#include<onerut_normal_operator/operator_abstract.hpp>
//#include<onerut_normal_operator/operator_simple.hpp>
//#include<onerut_normal_operator/operator_zero.hpp>
//#include<onerut_normal_operator/operator_oscillator.hpp>
//#include<onerut_normal_operator/to_mat.hpp>
//#include<onerut_normal_operator/diagonalizator.hpp>

#include<onerut_parser/asset_utility.hpp>
#include<onerut_parser/imperative_request.hpp>
#include<onerut_parser/function_factory_imperative_request.hpp>

namespace onerut_parser {

    Asset NormalOperatorExecRequestFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
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
        return Asset::from_value<onerut_parser::ExecRequest>(
                std::make_shared<onerut_parser::ExecRequestTyped<onerut_normal_operator::Eigs> >(normal_operator_eigs)
                );
        //assert(0);
    }

}
