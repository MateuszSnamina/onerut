#ifndef ONERUT_UTILITY_AST_ASSET_DFS_HPP
#define ONERUT_UTILITY_AST_ASSET_DFS_HPP

#include<functional>
#include<onerut_parser_exec/ast_asset.hpp>

namespace onerut {
    namespace utility {
        // TODO mode to cpp

        inline
        void
        dfs(
                std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode> head_node,
                std::function<void(const onerut_parser_exec::onerut_ast::asset::AssetNode&) > action) {
            assert(head_node);
            for (const auto sub_node : head_node->subnodes)
                dfs(sub_node, action);
            action(*head_node);
        }
    }
}

#endif 

