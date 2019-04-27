#include<iostream>
#include<iomanip>
#include<algorithm>
#include<functional>

#include<esc/esc_manip.hpp>
#include<onerut_convergence_parameter/convergence_parameter.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_request/request_print_value.hpp>
#include<onerut/aka.hpp>
#include<onerut/line_preprocessor.hpp>
#include<onerut/line_processor.hpp>
#include<onerut/execute_script.hpp>

void
print_section_bar(std::string section_title) {
    std::cout << std::endl;
    std::cout << esc::manip::bg_blue
            << std::setw(100) << std::left << "[DECLARATIVE MODE] [SECTION] [" + section_title + "]"
            << esc::manip::reset << std::endl;
}

template<class T>
void
add_if_type_matches(std::vector<std::shared_ptr<T> >& objects, onerut_parser_exec::Asset asset) {
    const auto asset_deref = asset.deref();
    if (asset_deref.is_either_value_or_type()) {
        if (const auto &object = asset_deref.typed_value_or_empty<T>()) {
            if (std::find(cbegin(objects), cend(objects), object) == cend(objects)) {
                objects.push_back(*object);
            }
        }
    }
}

void
dfs(std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode> head_node,
        std::function<void(onerut_parser_exec::Asset) > action) {
    for (const auto sub_node : head_node->subnodes)
        dfs(sub_node, action);
    action(head_node->asset);
}

void
execute_imparative_script(
        const std::vector<std::shared_ptr<const std::string>>&lines) {
    process_imperative_lines(preprocess_line(lines));
}

void
execute_declarative_script(
        const std::vector<std::shared_ptr<const std::string>>&lines,
        unsigned n_max_iterations) {
    // -------------------------------------------------------------------------
    print_section_bar("SCRIPT LINES PROCESSING");
    const auto ats_head_nodes = process_declarative_lines(preprocess_line(lines));
    // -------------------------------------------------------------------------
    print_section_bar("OBJECTS INVENTORYING");
    // -------------------------------------------------------------------------
    std::vector<std::shared_ptr<onerut_convergence_parameter::ConvergenceParameter> > convergence_parameter_objects;
    std::vector<std::shared_ptr<onerut_normal_operator::Eig> > eig_objects;
    std::vector<std::shared_ptr<onerut_normal_operator::Mean> > mean_objects;
    std::vector<std::shared_ptr<onerut_request::PrintValueRequest > > print_value_request_objects;
    // -------------------------------------------------------------------------
    for (const auto& ast_head_node : ats_head_nodes) {
        const auto add_convergence_parameter_objects = std::bind(
                add_if_type_matches<onerut_convergence_parameter::ConvergenceParameter>,
                std::ref(convergence_parameter_objects),
                std::placeholders::_1);
        dfs(ast_head_node, add_convergence_parameter_objects);
        const auto add_eig_objects = std::bind(
                add_if_type_matches<onerut_normal_operator::Eig>,
                std::ref(eig_objects),
                std::placeholders::_1);
        dfs(ast_head_node, add_eig_objects);
        const auto add_mean_objects = std::bind(
                add_if_type_matches<onerut_normal_operator::Mean>,
                std::ref(mean_objects),
                std::placeholders::_1);
        dfs(ast_head_node, add_mean_objects);
        const auto add_value_request_objects = std::bind(
                add_if_type_matches<onerut_request::PrintValueRequest>,
                std::ref(print_value_request_objects),
                std::placeholders::_1);
        dfs(ast_head_node, add_value_request_objects);
    }
    // -------------------------------------------------------------------------
    const auto akas_for_convergence_parameter_objects =
            create_object_akas_map<onerut_convergence_parameter::ConvergenceParameter>();
    const auto akas_for_eig_objects =
            create_object_akas_map<onerut_normal_operator::Eig>();
    const auto akas_for_mean_objects =
            create_object_akas_map<onerut_normal_operator::Mean>();
    const auto akas_for_print_value_request_objects =
            create_object_akas_map<onerut_request::PrintValueRequest>();
    // -------------------------------------------------------------------------
    for (const auto& object : convergence_parameter_objects) {
        std::cout << "[INVENTORY] " << "[CONVERGENCE PARAMETER] "
                << Aka(object, akas_for_convergence_parameter_objects) << std::endl;
    }
    for (const auto& object : eig_objects) {
        std::cout << "[INVENTORY] " << "[EIG] "
                << Aka(object, akas_for_eig_objects) << std::endl;
    }
    for (const auto& object : mean_objects) {
        std::cout << "[INVENTORY] " << "[MEAN] "
                << Aka(object, akas_for_mean_objects) << std::endl;
    }
    for (const auto& object : print_value_request_objects) {
        std::cout << "[INVENTORY] " << "[PRINT VALUE REQUEST] "
                << Aka(object, akas_for_print_value_request_objects) << std::endl;
    }
    // -------------------------------------------------------------------------
    // check if every convergence_parameter_objects has set expression.
    // -------------------------------------------------------------------------
    print_section_bar("SELF-CONSISTENT LOOP");
    // -------------------------------------------------------------------------    
    bool global_convergence = false;
    for (unsigned iteracja = 0; iteracja < n_max_iterations; ++iteracja) {
        std::cout << esc::manip::bg_yellow
                << "[DECLARATIVE MODE] [STEP] [SELF-CONSISTENT LOOP] [ITERATIONS] "
                << "iteration number " << std::setw(4) << iteracja << "."
                << esc::manip::reset
                << std::endl;
        for (const auto& request : print_value_request_objects) {
            std::cout << "[PRINT VALUE REQUEST] "
                    << Aka(request, akas_for_print_value_request_objects) << std::endl;
            request->print(std::cout, "[request] ");
        }
        for (const auto& object : convergence_parameter_objects) {
            object->recalcuate();
        }
        for (const auto& object : convergence_parameter_objects) {
            double old_value = object->value_real();
            object->revolve();
            double new_value = object->value_real();
            std::cout << "[CONVERGENCE PARAMETER] [OLD VALUE => NEW VALUE] "
                    << Aka(object, akas_for_convergence_parameter_objects) << " "
                    << old_value << "=>" << new_value
                    << std::endl;
        }
        bool global_convergence_accumulator = true;
        for (const auto& object : convergence_parameter_objects) {
            const bool is_converged = object->is_converged();
            std::cout << "[CONVERGENCE PARAMETER] [CONVERGENCE] ";
            if (is_converged) {
                std::cout << esc::manip::green << "✓" << esc::manip::reset;
            } else {
                std::cout << esc::manip::red << "✘" << esc::manip::reset;
                global_convergence_accumulator = false;
            }
            std::cout << " as Δ=" << object->delta_or_nan()
                    << " (threshold=" << object->threshold() << ")"
                    << std::endl;
        }
        if (global_convergence_accumulator) {
            global_convergence = true;
            break;
        }
    }
    std::cout << esc::manip::bg_yellow <<
            "[DECLARATIVE MODE] [STEP] [SELF-CONSISTENT LOOP] [SUMMARY]"
            << esc::manip::reset
            << std::endl;
    if (global_convergence) {
        std::cout << "[GLOBAL CONVERGENCE] " << esc::manip::green << "✓" << esc::manip::reset;
    } else {
        std::cout << "[GLOBAL CONVERGENCE] " << esc::manip::red << "✘" << esc::manip::reset;
    }
    std::cout << std::endl;
    for (const auto& request : print_value_request_objects) {
        std::cout << "[PRINT VALUE REQUEST] "
                << Aka(request, akas_for_print_value_request_objects) << std::endl;
        request->print(std::cout, "[request] ");
    }
    // -------------------------------------------------------------------------
}