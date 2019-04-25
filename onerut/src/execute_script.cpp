#include<onerut/line_processor.hpp>
#include<onerut/line_preprocessor.hpp>
#include<onerut/execute_script.hpp>

#include<algorithm>
#include<functional>

#include<onerut_parser_exec/asset_ref_container.hpp>
#include<onerut_normal_operator/eig.hpp>
//#include<onerut_normal_operator/mean.hpp>
#include<onerut_convergence_parameter/convergence_parameter.hpp>

template<class T>
void add_if_type_matches(std::vector<std::shared_ptr<T> >& objects, onerut_parser_exec::Asset asset) {
    const auto asset_deref = asset.deref();
    if (asset_deref.is_either_value_or_type()) {
        if (const auto &object = asset_deref.typed_value_or_empty<T>()) {
            //std::cout << "+" << (*object);
            if (std::find(cbegin(objects), cend(objects), object) == cend(objects)) {
                objects.push_back(*object);
            }
            //std::cout << "[" << objects.size() << "]" << std::endl;
        }
        //        else {
        //            std::cout << "-" << std::endl;
        //        }
    }
    //    else {
    //        std::cout << "!" << std::endl;
    //    }
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
}

void
execute_declarative_script(const std::vector<std::shared_ptr<const std::string>>&lines) {
    // -------------------------------------------------------------------------
    std::cout << "[DECLARATIVE MODE] [STEP] [SCRIPT LINES PROCESSING]" << std::endl;
    //std::vector<std::shared_ptr < onerut_parser_exec::onerut_ast::asset::AssetNode>>
    const auto ats_head_nodes = process_declarative_lines(preprocess_line(lines));
    // -------------------------------------------------------------------------
    std::cout << "[DECLARATIVE MODE] [STEP] [OBJECTS INVENTORYING]" << std::endl;
    std::vector<std::shared_ptr<onerut_normal_operator::Eig> > eig_objects;
    std::vector<std::shared_ptr<onerut_convergence_parameter::ConvergenceParameter> > convergence_parameter_objects;
    for (const auto& ast_head_node : ats_head_nodes) {
        //std::cout << "**************" << std::endl;
        const auto add_eig_objects = std::bind(
                add_if_type_matches<onerut_normal_operator::Eig>,
                std::ref(eig_objects),
                std::placeholders::_1);
        dfs(ast_head_node, add_eig_objects);
        const auto add_convergence_parameter_objects = std::bind(
                add_if_type_matches<onerut_convergence_parameter::ConvergenceParameter>,
                std::ref(convergence_parameter_objects),
                std::placeholders::_1);
        dfs(ast_head_node, add_convergence_parameter_objects);
        //std::cout << std::endl;
    }
    for (const auto& object : eig_objects) {
        std::cout << "[INVENTORY]" << "[EIG]" << object << std::endl;
    }
    for (const auto& object : convergence_parameter_objects) {
        std::cout << "[INVENTORY]" << "[CONVERGENCE PARAMETER]" << object << std::endl;
    }
    // -------------------------------------------------------------------------
    const auto& identifiers = onerut_parser_exec::AssetRefContainer::global_instance().identifiers();
    for (const auto& identifiers_entry : identifiers) {
        const auto& name = identifiers_entry.first;
        const auto& asset = identifiers_entry.second;
        assert(asset);
        const auto& asset_deref = asset->get_asset_deref();
        if (asset_deref.is_either_value_or_type()) {
            if (const auto &object = asset_deref.typed_value_or_empty<onerut_normal_operator::Eig>()) {
                std::cout << name << " " << *object << "---" << std::endl;
            }
        } else {
            std::cout << name << std::endl; // << identifiers_entry.second << std::end;
        }
    }
    // -------------------------------------------------------------------------
    std::cout << "[DECLARATIVE MODE] [STEP] [SELF-CONSISTENT LOOP]" << std::endl;

}
