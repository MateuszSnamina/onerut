#include<algorithm>
#include<iterator>

#include<onerut_parser_exec/share_from.hpp>
#include<onerut_parser_exec/ast_source.hpp>
#include<onerut_parser_exec/ast_asset.hpp>
#include<onerut_parser_exec/asset_utility.hpp>
#include<onerut_parser_exec/asset_ref_container.hpp>

namespace onerut_parser_exec::onerut_ast::source {

    namespace {

        std::vector<std::shared_ptr<onerut_ast::asset::AssetNode>>
        many_compile(
                std::shared_ptr<CompilerRules> compiler_rules,
                const std::vector<std::shared_ptr<onerut_ast::source::SourceNode>> argv) {
            std::vector<std::shared_ptr < onerut_ast::asset::AssetNode>> argv_node;
            argv_node.reserve(argv.size());
            std::transform(cbegin(argv), cend(argv), back_inserter(argv_node),
                    [&compiler_rules](const std::shared_ptr<onerut_ast::source::SourceNode> & arg) {
                        return arg->compile(compiler_rules);
                    });
            return argv_node;
        }

        std::vector<Asset>
        many_extract_asset(
                std::vector<std::shared_ptr<onerut_ast::asset::AssetNode>> argv_node) {
            std::vector<Asset> argv_asset;
            argv_asset.reserve(argv_node.size());
            std::transform(cbegin(argv_node), cend(argv_node), back_inserter(argv_asset),
                    [](const std::shared_ptr<onerut_ast::asset::AssetNode> &arg) {
                        return arg->asset;
                    });
            return argv_asset;
        }

    }

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    std::shared_ptr<asset::AssetNode>
    WithNoSubsourcesNode::compile(std::shared_ptr<CompilerRules> compiler_rules) const {
        const auto asset = basic_compile(compiler_rules);
        return std::make_shared<asset::AssetNode>(
                shared_from(this), asset);
    }

    std::shared_ptr<asset::AssetNode>
    WithOneSubsourceNode::compile(std::shared_ptr<CompilerRules> compiler_rules) const {
        std::shared_ptr<asset::AssetNode> arg_node = arg->compile(compiler_rules);
        const auto arg_asset = arg_node->asset;
        const auto asset = basic_compile(compiler_rules, arg_asset);
        return std::make_shared<asset::AssetNode>(
                shared_from(this), arg_node, asset);
    }

    std::shared_ptr<asset::AssetNode>
    WithTwoSubsourcesNode::compile(std::shared_ptr<CompilerRules> compiler_rules) const {
        std::shared_ptr<asset::AssetNode> first_arg_node = first_arg->compile(compiler_rules);
        std::shared_ptr<asset::AssetNode> second_arg_node = second_arg->compile(compiler_rules);
        const auto first_arg_asset = first_arg_node->asset;
        const auto second_arg_asset = second_arg_node->asset;
        const auto asset = basic_compile(compiler_rules, first_arg_asset, second_arg_asset);
        return std::make_shared<asset::AssetNode>(
                shared_from(this), first_arg_node, second_arg_node, asset);
    }

    std::shared_ptr<asset::AssetNode>
    WithOneOrMoreSubsourcesNode::compile(std::shared_ptr<CompilerRules> compiler_rules) const {
        const auto first_arg_node = first_arg->compile(compiler_rules);
        const auto other_argv_node = many_compile(compiler_rules, other_argv);
        const auto first_arg_asset = first_arg_node->asset;
        const auto other_argv_asset = many_extract_asset(other_argv_node);
        const auto asset = basic_compile(compiler_rules, first_arg_asset, other_argv_asset);
        return std::make_shared<asset::AssetNode>(
                shared_from(this), first_arg_node, other_argv_node, asset);
    }

    std::shared_ptr<asset::AssetNode>
    WithAnyNumberOfSubsourcesNode::compile(std::shared_ptr<CompilerRules> compiler_rules) const {
        const auto argv_node = many_compile(compiler_rules, argv);
        const auto argv_asset = many_extract_asset(argv_node);
        const auto asset = basic_compile(compiler_rules, argv_asset);
        return std::make_shared<asset::AssetNode>(
                shared_from(this), argv_node, asset);
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    Asset
    IdentifierNode::basic_compile(std::shared_ptr<CompilerRules> /*compiler_rules*/) const {
        if (auto ref = AssetRefContainer::global_instance().get_or_empty(name))
            return Asset::from_reference(*ref);
        return Asset::from_reference(std::make_shared<AssetUnsetRef>(name));
    }

    // -------------------------------------------------------------------------

    Asset
    OpAssignNode::basic_compile(std::shared_ptr<CompilerRules> /*compiler_rules*/, Asset first_arg_asset, Asset second_arg_asset) const {
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
            if (!AssetRefContainer::global_instance().put(created_ref)) {
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
                AssetRefContainer::global_instance().force_put(created_ref);
            }
            return second_arg_asset;
        }
        return Asset::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    Asset
    OpPlusMinusNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, std::vector<Asset> other_argv_asset) const {
        return compiler_rules->op_plus_minus(first_arg_asset, other_argv_asset, opv);
    }

    // -------------------------------------------------------------------------

    Asset
    OpProdDivNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, std::vector<Asset> other_argv_asset) const {
        return compiler_rules->op_prod_div(first_arg_asset, other_argv_asset, opv);
    }
    // -------------------------------------------------------------------------

    Asset
    OpPowNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const {
        return compiler_rules->op_pow(first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    OpAtNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const {
        return compiler_rules->op_at(first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    OpArrowNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const {
        return compiler_rules->op_arrow(first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    OpGlueNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const {
        return compiler_rules->op_glue(first_arg_asset, second_arg_asset);
    }

    // -------------------------------------------------------------------------

    Asset
    UnaryPlusMinusNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset arg_asset) const {
        return compiler_rules->op_unary_plus_minus(arg_asset, op);
    }

    // -------------------------------------------------------------------------

    Asset
    LitLongNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules) const {
        return compiler_rules->lit_long(value);
    }

    // -------------------------------------------------------------------------

    Asset
    LitDoubleNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules) const {
        return compiler_rules->lit_double(value);
    }

    // -------------------------------------------------------------------------

    Asset
    LitPureComplexDoubleNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules) const {
        return compiler_rules->lit_pure_complex_double(value);
    }

    // -------------------------------------------------------------------------

    Asset
    FunctionNode::basic_compile(std::shared_ptr<CompilerRules> compiler_rules, std::vector<Asset> argv_asset) const {
        return compiler_rules->function(name, argv_asset);
    }

}
