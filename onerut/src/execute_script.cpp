#include<onerut/line_processor.hpp>
#include<onerut/line_preprocessor.hpp>
#include<onerut/execute_script.hpp>

#include<functional>

#include<onerut_normal_operator/eig.hpp>
//#include<onerut_normal_operator/mean.hpp>

// onerut_convergence_parameter::ConvergenceParameter

//TRY:

void find_eig(onerut_parser_exec::Asset asset) {
    if (asset.deref().is_either_value_or_type()) {
        if (const auto &eig = asset.deref().typed_value_or_empty<onerut_normal_operator::Eig>()) {
            std::cout << "+" << (*eig) << std::endl;
        } else
            std::cout << "-" << std::endl;
    } else {
        std::cout << "!" << std::endl;
    }
}

void dfs(std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode> head_node,
        std::function<void(onerut_parser_exec::Asset) > action) {
    for (const auto sub_node : head_node->subnodes)
        dfs(sub_node, action);
    action(head_node->asset);
}

void
execute_imparative_script(const std::vector<std::shared_ptr<const std::string>>&lines) {
    process_imperative_lines(preprocess_line(lines));
    //execute_script_lines(lines);
    //return execute_script_lines(lines);
}

void
execute_declarative_script(const std::vector<std::shared_ptr<const std::string>>&lines) {

    //std::vector<std::shared_ptr < onerut_parser_exec::onerut_ast::asset::AssetNode>>
    const auto ats_head_nodes = process_declarative_lines(preprocess_line(lines));
    for (const auto& ast_head_node : ats_head_nodes) {
        std::cout << "**************" << std::endl;
        dfs(ast_head_node, find_eig);
        std::cout << std::endl;
    }
    //execute_script_lines(lines);
    //return execute_script_lines(lines);
}
