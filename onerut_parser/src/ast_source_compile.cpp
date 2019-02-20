#include<algorithm>
#include<iterator>

#include<onerut_parser/share_from.hpp>
#include<onerut_parser/ast_asset.hpp>
#include<onerut_parser/asset_utility.hpp>
#include<onerut_parser/ast_source.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_parser/function_factory_global.hpp>
#include<onerut_scalar/scalar.hpp>
#include<onerut_operator/operator.hpp>

namespace {

    bool
    is_plus_munis_char(char op) {
        return op == L'+' || op == L'-';
    }

    bool
    is_prod_div_char(char op) {
        return op == L'*' || op == L'/';
    }

    std::vector<std::shared_ptr < onerut_parser::onerut_ast::asset::AssetNode>>
    many_compile(
            const std::vector<std::shared_ptr<onerut_parser::onerut_ast::source::SourceNode>> argv) {
        std::vector<std::shared_ptr < onerut_parser::onerut_ast::asset::AssetNode>> argv_node;
        argv_node.reserve(argv.size());
        std::transform(cbegin(argv), cend(argv), back_inserter(argv_node),
                [](const std::shared_ptr<onerut_parser::onerut_ast::source::SourceNode> & arg) {
                    return arg->compile();
                });
        return argv_node;
    }

    std::vector<onerut_parser::Asset>
    many_extract_asset(
            std::vector<std::shared_ptr < onerut_parser::onerut_ast::asset::AssetNode>> argv_node) {
        std::vector<onerut_parser::Asset> argv_asset;
        argv_asset.reserve(argv_node.size());
        std::transform(cbegin(argv_node), cend(argv_node), back_inserter(argv_asset),
                [](const std::shared_ptr < onerut_parser::onerut_ast::asset::AssetNode> &arg) {
                    return arg->asset;
                });
        return argv_asset;
    }

    //    bool
    //    many_is_either_value_or_type(
    //            onerut_parser::AssetDeref first_arg_asset,
    //            onerut_parser::AssetDeref second_arg_asset) {
    //        return first_arg_asset.is_either_value_or_type() &&
    //                second_arg_asset.is_either_value_or_type();
    //    }

    bool
    many_is_either_value_or_type(
            onerut_parser::AssetDeref first_arg_asset,
            std::vector<onerut_parser::AssetDeref> other_argv_asset) {
        return first_arg_asset.is_either_value_or_type() &&
                std::all_of(other_argv_asset.cbegin(), other_argv_asset.cend(),
                [](const onerut_parser::AssetDeref & asset) {
                    return asset.is_either_value_or_type();
                });
    }

    //    bool
    //    many_is_either_value_or_type(std::vector<onerut_parser::AssetDeref> argv_asset) {
    //        return std::all_of(argv_asset.cbegin(), argv_asset.cend(),
    //                [](const onerut_parser::AssetDeref & asset) {
    //                    return asset.is_either_value_or_type();
    //                });
    //    }

    onerut_parser::Asset
    behave_like_a_binary_function(
            const std::string function_name,
            onerut_parser::Asset first_arg_asset,
            onerut_parser::Asset second_arg_asset) {
        const auto first_arg_asset_deref = first_arg_asset.deref();
        const auto second_arg_asset_deref = second_arg_asset.deref();
        if (auto function_factory = onerut_parser::GlobalFunctionFactories::instance().get_or_empty(function_name))
            return (*function_factory)->make_function_otherwise_make_error({first_arg_asset, second_arg_asset});
        return onerut_parser::Asset::from_compile_error(std::make_shared<onerut_parser::FunctionNotFoundError>(function_name));
    }

}

namespace onerut_parser::onerut_ast::source {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    std::shared_ptr<onerut_parser::onerut_ast::asset::AssetNode>
    WithNoSubsourcesNode::compile() const {
        const auto asset = basic_compile();
        return std::make_shared<onerut_parser::onerut_ast::asset::AssetNode>(
                shared_from(this), asset);
    }

    std::shared_ptr<onerut_parser::onerut_ast::asset::AssetNode>
    WithOneSubsourceNode::compile() const {
        std::shared_ptr<onerut_parser::onerut_ast::asset::AssetNode> arg_node = arg->compile();
        const auto arg_asset = arg_node->asset;
        const auto asset = basic_compile(arg_asset);
        return std::make_shared<onerut_parser::onerut_ast::asset::AssetNode>(
                shared_from(this), arg_node, asset);
    }

    std::shared_ptr<onerut_parser::onerut_ast::asset::AssetNode>
    WithTwoSubsourcesNode::compile() const {
        std::shared_ptr<onerut_parser::onerut_ast::asset::AssetNode> first_arg_node = first_arg->compile();
        std::shared_ptr<onerut_parser::onerut_ast::asset::AssetNode> second_arg_node = second_arg->compile();
        const auto first_arg_asset = first_arg_node->asset;
        const auto second_arg_asset = second_arg_node->asset;
        const auto asset = basic_compile(first_arg_asset, second_arg_asset);
        return std::make_shared<onerut_parser::onerut_ast::asset::AssetNode>(
                shared_from(this), first_arg_node, second_arg_node, asset);
    }

    std::shared_ptr<onerut_parser::onerut_ast::asset::AssetNode>
    WithOneOrMoreSubsourcesNode::compile() const {
        const auto first_arg_node = first_arg->compile();
        const auto other_argv_node = many_compile(other_argv);
        const auto first_arg_asset = first_arg_node->asset;
        const auto other_argv_asset = many_extract_asset(other_argv_node);
        const auto asset = basic_compile(first_arg_asset, other_argv_asset);
        return std::make_shared<onerut_parser::onerut_ast::asset::AssetNode>(
                shared_from(this), first_arg_node, other_argv_node, asset);
    }

    std::shared_ptr<onerut_parser::onerut_ast::asset::AssetNode>
    WithAnyNumberOfSubsourcesNode::compile() const {
        const auto argv_node = many_compile(argv);
        const auto argv_asset = many_extract_asset(argv_node);
        const auto asset = basic_compile(argv_asset);
        return std::make_shared<onerut_parser::onerut_ast::asset::AssetNode>(
                shared_from(this), argv_node, asset);
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    Asset
    IdentifierNode::basic_compile() const {
        if (auto holder = GlobalIdentifiers::instance().get_or_empty(name))
            return Asset::from_reference(*holder);
        return Asset::from_reference(std::make_shared<AssetUnsetRef>(name));
        //return Asset::from_compile_error(std::make_shared<IdentifierNotFoundError>(name));
    }

    // -------------------------------------------------------------------------

    Asset
    OpAssignNode::basic_compile(Asset first_arg_asset, Asset second_arg_asset) const {
        const auto second_arg_asset_deref = second_arg_asset.deref();
        const auto first_arg_asset_deref = first_arg_asset.deref();
        const bool first_arg_is_not_const_ref = utility::is_not_const_ref(first_arg_asset);
        const bool first_arg_is_const_ref = utility::is_const_ref(first_arg_asset);
        const bool first_arg_is_unset_ref = utility::is_unset_ref(first_arg_asset);
        const bool first_arg_type_match = first_arg_is_not_const_ref || first_arg_is_const_ref || first_arg_is_unset_ref;
        const bool second_argument_match = second_arg_asset_deref.is_either_value_or_type();
        if (!second_argument_match)
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!first_arg_type_match)
            return Asset::from_compile_error(std::make_shared<IllegalAssignAttemptToRValueError>());
        if (first_arg_is_const_ref)
            return Asset::from_compile_error(std::make_shared<IllegalAssignAttemptToConstReferenceError>());
        if (new_flag && !first_arg_is_unset_ref)
            return Asset::from_compile_error(std::make_shared<IllegalAssignAttemptToSetReferenceError>());
        if (first_arg_is_unset_ref) {
            const auto name = utility::name_of_unset_ref(first_arg_asset);
            const std::shared_ptr<AbstractAssetRef> created_ref = const_flag ?
                    std::static_pointer_cast<AbstractAssetRef>(std::make_shared<AssetConstRef>(name, second_arg_asset_deref)) :
                    std::static_pointer_cast<AbstractAssetRef>(std::make_shared<AssetNotConstRef>(name, second_arg_asset_deref));
            if (!GlobalIdentifiers::instance().put(name, created_ref)) {
                return Asset::from_compile_error(std::make_shared<IllegalSecondAssignError>());
            }
            return second_arg_asset;
        }
        if (first_arg_is_not_const_ref) {
            auto ref = utility::to_not_const_ref(first_arg_asset);
            if (!const_flag) {
                ref->set_asset(second_arg_asset_deref);
            } else {
                const auto name = ref->get_name();
                const auto created_ref = std::make_shared<AssetConstRef>(name, second_arg_asset_deref);
                GlobalIdentifiers::instance().force_put(name, created_ref);
            }
            return second_arg_asset;
        }
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    Asset
    OpPlusMinusNode::basic_compile(Asset first_arg_asset, std::vector<Asset> other_argv_asset) const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_plus_munis_char));
        const auto & first_arg_asset_deref = first_arg_asset.deref();
        const auto & other_argv_asset_deref = utility::many_deref(other_argv_asset);
        if (!many_is_either_value_or_type(first_arg_asset_deref, other_argv_asset_deref))
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
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
        //        if (utility::is_normal_operator(first_arg_asset_deref) &&
        //                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_normal_operator)) {
        //            const auto & first_arg_operator = utility::to_normal_operator(first_arg_asset_deref);
        //            const auto & other_argv_operator = utility::many_to_normal_operator(other_argv_asset_deref);
        //            using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        //            return Asset::from_value<AbstractOperatorT>(std::make_shared<onerut_normal_operator::OpPlusMinusOperator >(first_arg_operator, other_argv_operator, opv));
        //        }
        return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    Asset
    OpProdDivNode::basic_compile(Asset first_arg_asset, std::vector<Asset> other_argv_asset) const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_prod_div_char));
        const auto & first_deref_arg_asset = first_arg_asset.deref();
        const auto & other_argv_asset_deref = utility::many_deref(other_argv_asset);
        if (!many_is_either_value_or_type(first_deref_arg_asset, other_argv_asset_deref))
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (utility::is_integer(first_deref_arg_asset) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_integer)) {
            const auto & first_arg_integer = utility::to_integer(first_deref_arg_asset);
            const auto & other_argv_integer = utility::many_to_integer(other_argv_asset_deref);
            return Asset::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::OpProdDivInteger>(first_arg_integer, other_argv_integer, opv));
        }
        if (utility::is_real_or_integer(first_deref_arg_asset) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_real_or_integer)) {
            const auto & first_arg_real = utility::to_real(first_deref_arg_asset);
            const auto & other_argv_real = utility::many_to_real(other_argv_asset_deref);
            return Asset::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::OpProdDivReal>(first_arg_real, other_argv_real, opv));
        }
        if (utility::is_real_or_integer_or_complex(first_deref_arg_asset) &&
                std::all_of(cbegin(other_argv_asset_deref), cend(other_argv_asset_deref), utility::is_real_or_integer_or_complex)) {
            const auto & first_arg_complex = utility::to_complex(first_deref_arg_asset);
            const auto & other_argv_complex = utility::many_to_complex(other_argv_asset_deref);
            return Asset::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::OpProdDivComplex>(first_arg_complex, other_argv_complex, opv));
        }
        return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    Asset
    OpPowNode::basic_compile(Asset first_arg_asset, Asset second_arg_asset) const {
        return behave_like_a_binary_function("pow", first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    OpAtNode::basic_compile(Asset first_arg_asset, Asset second_arg_asset) const {
        return behave_like_a_binary_function("at", first_arg_asset, second_arg_asset);

    }

    // -------------------------------------------------------------------------

    Asset
    OpArrowNode::basic_compile(Asset first_arg_asset, Asset second_arg_asset) const {
        return behave_like_a_binary_function("arrow", first_arg_asset, second_arg_asset);

    }

    // -------------------------------------------------------------------------

    Asset
    OpGlueNode::basic_compile(Asset first_arg_asset, Asset second_arg_asset) const {
        return behave_like_a_binary_function("glue", first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    UnaryPlusMinusNode::basic_compile(Asset arg_asset) const {
        const auto arg_asset_deref = arg_asset.deref();
        assert(is_plus_munis_char(op));
        assert(!arg_asset_deref.is_empty());
        if (!arg_asset_deref.is_either_value_or_type())
            const Asset asset = Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
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
        return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    Asset
    LitLongNode::basic_compile() const {
        return Asset::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::LitInteger>(value));
    }

    // -------------------------------------------------------------------------

    Asset
    LitDoubleNode::basic_compile() const {
        return Asset::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::LitReal>(value));
    }

    // -------------------------------------------------------------------------

    Asset
    LitPureComplexDoubleNode::basic_compile() const {
        return Asset::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::LitComplex>(std::complex(0.0, value)));
    }

    // -------------------------------------------------------------------------

    Asset
    FunctionNode::basic_compile(std::vector<Asset> argv_asset) const {
        if (auto function = GlobalFunctionFactories::instance().get_or_empty(name))
            return (*function)->make_function_otherwise_make_error(argv_asset);
        return Asset::from_compile_error(std::make_shared<FunctionNotFoundError>(name));
    }

}
