#include<algorithm>
#include<iterator>

#include<onerut_scalar/scalar.hpp>
#include<onerut_normal_operator/operator_opplusminus.hpp>
#include<onerut_normal_operator/operator_opprod.hpp>
#include<onerut_normal_operator/operator_scalled.hpp>
#include<onerut_normal_operator/operator_opunaryplusminus.hpp>
#include<onerut_parser_exec/vector_cat.hpp>
#include<onerut_parser_exec/ast_asset.hpp>
#include<onerut_parser_exec/asset_utility.hpp>
#include<onerut_parser_rules/asset_utility_concrete.hpp>
#include<onerut_parser_rules/compiler_rules_concrete.hpp>

namespace {

    bool
    is_plus_munis_char(char op) {
        return op == '+' || op == '-';
    }

    bool
    is_prod_div_char(char op) {
        return op == '*' || op == '/';
    }

    bool
    is_prod_char(char op) {
        return op == '*';
    }

    onerut_parser::Asset
    behave_like_a_binary_function(
            const onerut_parser::FunctionFactoryContainer & function_factory_container,
            const std::string & function_name,
            onerut_parser::Asset first_arg_asset,
            onerut_parser::Asset second_arg_asset) {
        const auto first_arg_asset_deref = first_arg_asset.deref();
        const auto second_arg_asset_deref = second_arg_asset.deref();
        if (auto function_factory = function_factory_container.get_or_empty(function_name))
            return (*function_factory)->make_function_otherwise_make_error({first_arg_asset, second_arg_asset});
        return onerut_parser::Asset::from_compile_error(std::make_shared<onerut_parser::FunctionNotFoundError>(function_name));
    }

}

namespace onerut_parser {

    CompilerRulesConcrete::CompilerRulesConcrete() {
        function_factory_container.put_all();
    }

    Asset
    CompilerRulesConcrete::op_plus_minus(Asset first_arg_asset, std::vector<Asset> other_argv_asset, std::vector<char> opv) const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_plus_munis_char));
        const auto & first_arg_asset_deref = first_arg_asset.deref();
        const auto & other_argv_asset_deref = utility::many_deref(other_argv_asset);
        if (utility::any_of_is_compile_error(first_arg_asset_deref, other_argv_asset_deref))
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::all_of_is_either_value_or_type(first_arg_asset_deref, other_argv_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (utility::is_integer(first_arg_asset_deref) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_integer)) {
            const auto & first_arg_integer = utility::to_integer(first_arg_asset_deref);
            const auto & other_argv_integer = utility::many_to_integer(other_argv_asset_deref);
            return Asset::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::OpPlusMinusInteger>(first_arg_integer, other_argv_integer, opv));
        }
        if (utility::is_real_or_integer(first_arg_asset_deref) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_real_or_integer)) {
            const auto & first_arg_real = utility::to_real(first_arg_asset_deref);
            const auto & other_argv_real = utility::many_to_real(other_argv_asset_deref);
            return Asset::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::OpPlusMinusReal>(first_arg_real, other_argv_real, opv));
        }
        if (utility::is_real_or_integer_or_complex(first_arg_asset_deref) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_real_or_integer_or_complex)) {
            const auto & first_arg_complex = utility::to_complex(first_arg_asset_deref);
            const auto & other_argv_complex = utility::many_to_complex(other_argv_asset_deref);
            return Asset::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::OpPlusMinusComplex>(first_arg_complex, other_argv_complex, opv));
        }
        if (utility::is_normal_operator(first_arg_asset_deref) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_normal_operator)) {
            const auto & first_arg_operator = utility::to_normal_operator(first_arg_asset_deref);
            const auto & other_argv_operator = utility::many_to_normal_operator(other_argv_asset_deref);
            if (!are_the_same_domains(first_arg_operator, other_argv_operator))
                return Asset::from_compile_error(std::make_shared<ArgumentDomainError>("Incompatible operator domains."));
            using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
            return Asset::from_value<AbstractRealOperatorT>(std::make_shared<onerut_normal_operator::OpPlusMinusOperator >(first_arg_operator, other_argv_operator, opv));
        }
        return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------    

    Asset
    CompilerRulesConcrete::op_prod_div(Asset first_arg_asset, std::vector<Asset> other_argv_asset, std::vector<char> opv) const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_prod_div_char));
        const auto & first_arg_asset_deref = first_arg_asset.deref();
        const auto & other_argv_asset_deref = utility::many_deref(other_argv_asset);
        if (utility::any_of_is_compile_error(first_arg_asset_deref, other_argv_asset_deref))
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::all_of_is_either_value_or_type(first_arg_asset_deref, other_argv_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (utility::is_integer(first_arg_asset_deref) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_integer)) {
            const auto & first_arg_integer = utility::to_integer(first_arg_asset_deref);
            const auto & other_argv_integer = utility::many_to_integer(other_argv_asset_deref);
            return Asset::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::OpProdDivInteger>(first_arg_integer, other_argv_integer, opv));
        }
        if (utility::is_real_or_integer(first_arg_asset_deref) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_real_or_integer)) {
            const auto & first_arg_real = utility::to_real(first_arg_asset_deref);
            const auto & other_argv_real = utility::many_to_real(other_argv_asset_deref);
            return Asset::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::OpProdDivReal>(first_arg_real, other_argv_real, opv));
        }
        if (utility::is_real_or_integer_or_complex(first_arg_asset_deref) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_real_or_integer_or_complex)) {
            const auto & first_arg_complex = utility::to_complex(first_arg_asset_deref);
            const auto & other_argv_complex = utility::many_to_complex(other_argv_asset_deref);
            return Asset::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::OpProdDivComplex>(first_arg_complex, other_argv_complex, opv));
        }
        if (std::all_of(opv.cbegin(), opv.cend(), is_prod_char) &&
                utility::is_normal_operator(first_arg_asset_deref) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_normal_operator)) {
            const auto & first_arg_operator = utility::to_normal_operator(first_arg_asset_deref);
            const auto & other_argv_operator = utility::many_to_normal_operator(other_argv_asset_deref);
            if (!are_the_same_domains(first_arg_operator, other_argv_operator))
                return Asset::from_compile_error(std::make_shared<ArgumentDomainError>("Incompatible operator domains."));
            const auto argv_operator = cat(first_arg_operator, other_argv_operator);
            using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
            return Asset::from_value<AbstractRealOperatorT>(std::make_shared<onerut_normal_operator::OpProdOperator >(argv_operator));
        }
        if (other_argv_asset_deref.size() == 1 && opv[0] == '*' &&
                utility::is_real_or_integer(first_arg_asset_deref) &&
                utility::is_normal_operator(other_argv_asset_deref[0])) {
            const auto & first_arg_operator = utility::to_real(first_arg_asset_deref);
            const auto & second_arg_operator = utility::to_normal_operator(other_argv_asset_deref[0]);
            using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
            return Asset::from_value<AbstractRealOperatorT>(std::make_shared<onerut_normal_operator::ScalledOperator>(first_arg_operator, second_arg_operator));
        }
        return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    Asset
    CompilerRulesConcrete::op_pow(Asset first_arg_asset, Asset second_arg_asset) const {
        return behave_like_a_binary_function(function_factory_container, "pow", first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    CompilerRulesConcrete::op_at(Asset first_arg_asset, Asset second_arg_asset) const {
        return behave_like_a_binary_function(function_factory_container, "at", first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    CompilerRulesConcrete::op_arrow(Asset first_arg_asset, Asset second_arg_asset) const {
        return behave_like_a_binary_function(function_factory_container, "arrow", first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    CompilerRulesConcrete::op_glue(Asset first_arg_asset, Asset second_arg_asset) const {
        return behave_like_a_binary_function(function_factory_container, "glue", first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    CompilerRulesConcrete::op_unary_plus_minus(Asset arg_asset, char op) const {
        const auto arg_asset_deref = arg_asset.deref();
        assert(is_plus_munis_char(op));
        if (arg_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!arg_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        assert(!arg_asset_deref.is_empty());
        if (utility::is_integer(arg_asset_deref)) {
            const auto & arg_integer = utility::to_integer(arg_asset_deref);
            return Asset::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::OpUnaryPlusMinusInteger>(arg_integer, op));
        }
        if (utility::is_real_or_integer(arg_asset_deref)) {
            const auto & arg_real = utility::to_real(arg_asset_deref);
            return Asset::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::OpUnaryPlusMinusReal>(arg_real, op));
        }
        if (utility::is_real_or_integer_or_complex(arg_asset_deref)) {
            const auto & arg_complex = utility::to_complex(arg_asset_deref);
            return Asset::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::OpUnaryPlusMinusComplex>(arg_complex, op));
        }
        if (utility::is_normal_operator(arg_asset_deref)) {
            const auto & arg_operator = utility::to_normal_operator(arg_asset_deref);
            using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
            return Asset::from_value<AbstractRealOperatorT>(std::make_shared<onerut_normal_operator::OpUnaryPlusMinusOperator>(arg_operator, op));
        }
        return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    Asset
    CompilerRulesConcrete::lit_long(long value) const {
        return Asset::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::LitInteger>(value));
    }

    // -------------------------------------------------------------------------

    Asset
    CompilerRulesConcrete::lit_double(double value) const {
        return Asset::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::LitReal>(value));
    }

    // -------------------------------------------------------------------------

    Asset
    CompilerRulesConcrete::lit_pure_complex_double(double value) const {
        return Asset::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::LitComplex>(std::complex(0.0, value)));
    }

    // -------------------------------------------------------------------------

    Asset
    CompilerRulesConcrete::function(const std::string& name, const std::vector<Asset>& argv_asset) const {
        if (auto function = function_factory_container.get_or_empty(name))
            return (*function)->make_function_otherwise_make_error(argv_asset);
        return Asset::from_compile_error(std::make_shared<FunctionNotFoundError>(name));
    }

}