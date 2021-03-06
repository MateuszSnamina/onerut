#ifndef ONERUT_GREP_AST_ASSET_HPP
#define ONERUT_GREP_AST_ASSET_HPP

#include<string>
#include<map>
#include<memory>

#include<onerut/utility_ptr_map.hpp>
#include<onerut/utility_ast_asset_dfs.hpp>

namespace {

    template<class T>
    void
    add_source_if_type_matches(
            utility::weak_ptr_map<T, std::string>& source_code_for_objects,
            const onerut_parser_exec::onerut_ast::asset::AssetNode & asset_node) {
        const auto asset = asset_node.asset;
        const auto asset_deref = asset.deref();
        if (asset_deref.is_either_value_or_type()) {
            if (const auto &object = asset_deref.typed_value_or_empty<T>()) {
                const bool already_added = source_code_for_objects.count(*object);
                if (!already_added) {
                    source_code_for_objects[*object] =
                            string_utils::to_string(asset_node.source->span);
                }
            }
        }
    }

} // end of anonymous namespace


//namespace onerut {

/*
 * The function scans ast-asset 
 * in search for nodes associated with assets holding value of type T.
 */

template<class T>
utility::weak_ptr_map<T, std::string>
grep_ast_asset(
        std::vector<std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>> ats_head_nodes) {
    utility::weak_ptr_map<T, std::string> result;
    for (const auto& ast_head_node : ats_head_nodes) {
        const auto add_convergence_parameter_objects = std::bind(
                add_source_if_type_matches<T>,
                std::ref(result),
                std::placeholders::_1);
        onerut::utility::dfs(ast_head_node, add_convergence_parameter_objects);
    }
    return result;
}

//}

#endif