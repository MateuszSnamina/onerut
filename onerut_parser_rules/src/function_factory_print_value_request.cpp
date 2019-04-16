#include<optional>

#include<onerut_parser_rules/request_print_value.hpp>
#include<onerut_parser_rules/function_factory_print_value_request.hpp>

namespace {

    std::optional<onerut_parser_exec::Asset>
    _try_with_error(onerut_parser_exec::AssetDeref arg) {
        if (arg.is_compile_error()) {
            const auto error = *arg.compile_error_or_empty();
            return onerut_parser_exec::Asset::from_value<onerut_parser_rules::PrintValueRequest>(
                    std::make_shared<onerut_parser_rules::PrintValueRequestTyped < onerut_parser_exec::CompileError >> (error)
                    );
        }
        return std::nullopt;
    }

    template<typename T>
    std::optional<onerut_parser_exec::Asset>
    _try_with_value(onerut_parser_exec::AssetDeref arg) {
        if (arg.is_given_type<T>()) {
            const auto arg_typed = *(arg.typed_value_or_empty<T>());
            return onerut_parser_exec::Asset::from_value<onerut_parser_rules::PrintValueRequest>(
                    std::make_shared<onerut_parser_rules::PrintValueRequestTyped < T > > (arg_typed)
                    );
        }
        return std::nullopt;
    }

}

namespace onerut_parser_rules {

    onerut_parser_exec::Asset PrintValueRequestFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        if (arg0_asset_deref.is_compile_error()) {
            const auto error = *arg0_asset_deref.compile_error_or_empty();
            return onerut_parser_exec::Asset::from_value<PrintValueRequest>(
                    std::make_shared<PrintValueRequestTyped<onerut_parser_exec::CompileError> >(error)
                    );
        }
        if (const auto temp = _try_with_error(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_scalar::Integer>(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_scalar::Real>(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_scalar::Complex>(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_normal_operator::CustomDomain>(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_normal_operator::OscillatorDomain>(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_normal_operator::SpinDomain>(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_normal_operator::KronDomain>(arg0_asset_deref)) {
            return *temp;
        }        
        if (const auto temp = _try_with_value<onerut_normal_operator::StateIndex>(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_normal_operator::KronPlaceholder>(arg0_asset_deref)) {
            return *temp;
        }        
        if (const auto temp = _try_with_value<onerut_normal_operator::AbstractRealOperator>(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_normal_operator::Eig>(arg0_asset_deref)) {
            return *temp;
        }
        if (const auto temp = _try_with_value<onerut_normal_operator::Mean>(arg0_asset_deref)) {
            return *temp;
        }
        return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
    }

}
