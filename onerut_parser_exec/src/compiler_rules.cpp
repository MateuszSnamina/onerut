#include<onerut_parser_exec/compiler_rules.hpp>
#include<onerut_parser_exec/asset_error.hpp>

namespace onerut_parser {

    Asset CompilerRules::op_plus_minus(Asset first_arg_asset, std::vector<Asset> other_argv_asset, std::vector<char> opv) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::op_prod_div(Asset first_arg_asset, std::vector<Asset> other_argv_asset, std::vector<char> opv) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::op_pow(Asset first_arg_asset, Asset second_arg_asset) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::op_at(Asset first_arg_asset, Asset second_arg_asset) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::op_arrow(Asset first_arg_asset, Asset second_arg_asset) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::op_glue(Asset first_arg_asset, Asset second_arg_asset) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::op_unary_plus_minus(Asset arg_asset, char op) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::lit_long(long value) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::lit_double(double value) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::lit_pure_complex_double(double value) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    Asset CompilerRules::function(const std::string & name, const std::vector<Asset> & argv_asset) const {
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

}