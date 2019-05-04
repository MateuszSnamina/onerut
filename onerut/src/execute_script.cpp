#include<iostream>
#include<iomanip>
#include<algorithm>
#include<functional>

#include<esc/esc_manip.hpp>
#include<string_utils/string_span.hpp>
#include<onerut_dependence/dependence_dfs.hpp>
#include<onerut_convergence_parameter/convergence_parameter.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_request/request_print_value.hpp>
#include<onerut/aka.hpp>
#include<onerut/line_preprocessor.hpp>
#include<onerut/line_processor.hpp>
#include<onerut/execute_script.hpp>

bool
dependence_is_convergence_parameter(std::shared_ptr<const onerut_dependence::Dependable> dependable) {
    using CastedT = onerut_convergence_parameter::ConvergenceParameter;
    assert(dependable);
    const auto dependable_casted = std::dynamic_pointer_cast<const CastedT>(dependable);
    return static_cast<bool> (dependable_casted);
}

bool
dependence_is_eig(std::shared_ptr<const onerut_dependence::Dependable> dependable) {
    using CastedT = onerut_normal_operator::Eig;
    assert(dependable);
    const auto dependable_casted = std::dynamic_pointer_cast<const CastedT>(dependable);
    return static_cast<bool> (dependable_casted);
}

bool
dependence_is_mean(std::shared_ptr<const onerut_dependence::Dependable> dependable) {
    using CastedT = onerut_normal_operator::Mean;
    assert(dependable);
    const auto dependable_casted = std::dynamic_pointer_cast<const CastedT>(dependable);
    return static_cast<bool> (dependable_casted);
}

std::vector<std::shared_ptr<const onerut_normal_operator::Eig>>
dependence_filter_eig(std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependences) {
    using CastedT = onerut_normal_operator::Eig;
    std::vector<std::shared_ptr<const CastedT>> result;
    for (const auto& dependence : dependences) {
        const auto& dependence_shared = dependence.lock();
        assert(dependence_shared);
        const auto dependence_casted = std::dynamic_pointer_cast<const CastedT>(dependence_shared);
        if (dependence_casted) {
            result.push_back(dependence_casted);
        }
    }
    return result;
}

std::vector<std::shared_ptr<const onerut_normal_operator::Mean>>
dependence_filter_mean(std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependences) {
    using CastedT = onerut_normal_operator::Mean;
    std::vector<std::shared_ptr<const CastedT>> result;
    for (const auto& dependence : dependences) {
        const auto& dependence_shared = dependence.lock();
        assert(dependence_shared);
        const auto dependence_casted = std::dynamic_pointer_cast<const CastedT>(dependence_shared);
        if (dependence_casted) {
            result.push_back(dependence_casted);
        }
    }
    return result;
}

void
print_section_bar(std::string section_title) {
    std::cout << std::endl;
    std::cout << esc::manip::bg_blue
            << std::setw(100) << std::left << "[DECLARATIVE MODE] [SECTION] [" + section_title + "]"
            << esc::manip::reset << std::endl;
}

template<class T>
void
add_if_type_matches(
        std::vector<std::shared_ptr<T> >& objects,
        std::map<std::shared_ptr<const void>, std::string>& source_code_for_objects,
        const onerut_parser_exec::onerut_ast::asset::AssetNode & asset_node) {
    const auto asset = asset_node.asset;
    const auto asset_deref = asset.deref();
    if (asset_deref.is_either_value_or_type()) {
        if (const auto &object = asset_deref.typed_value_or_empty<T>()) {
            if (std::find(cbegin(objects), cend(objects), object) == cend(objects)) {
                objects.push_back(*object);
                source_code_for_objects[*object] =
                        string_utils::to_string(asset_node.source->span);
            }
        }
    }
}

void
dfs(std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode> head_node,
        std::function<void(const onerut_parser_exec::onerut_ast::asset::AssetNode&) > action) {
    assert(head_node);
    for (const auto sub_node : head_node->subnodes)
        dfs(sub_node, action);
    action(*head_node);
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
    // *************************************************************************
    // *************************************************************************    
    print_section_bar("SCRIPT LINES PROCESSING");
    // -------------------------------------------------------------------------
    const auto ats_head_nodes = process_declarative_lines(preprocess_line(lines));
    // -------------------------------------------------------------------------
    for (const auto& ast_head_node : ats_head_nodes) {
        if (!ast_head_node) {
            std::cout << "[SCRIPT LINES PROCESSING] "
                    << esc::manip::bg_red << "[ERROR]" << esc::manip::reset << " "
                    << "One (or more) of the script lines is a parse error."
                    << std::endl;
            std::cout << "[SCRIPT LINES PROCESSING] "
                    << esc::manip::bg_red << "[ERROR]" << esc::manip::reset << " "
                    << "Termination of the script execution."
                    << std::endl;
            return;
        }
    }
    for (const auto& ast_head_node : ats_head_nodes) {
        const auto asset = ast_head_node->asset;
        const auto asset_deref = asset.deref();
        if (asset_deref.is_compile_error()) {
            std::cout << "[SCRIPT LINES PROCESSING] "
                    << esc::manip::bg_red << "[ERROR]" << esc::manip::reset << " "
                    << "One (or more) of the script lines as an compile error."
                    << std::endl;
            std::cout << "[SCRIPT LINES PROCESSING] "
                    << esc::manip::bg_red << "[ERROR]" << esc::manip::reset << " "
                    << "Termination of the script execution."
                    << std::endl;
            return;
        }
    }
    // *************************************************************************
    // *************************************************************************    
    print_section_bar("OBJECTS INVENTORYING");
    // -------------------------------------------------------------------------
    std::vector<std::shared_ptr<onerut_convergence_parameter::ConvergenceParameter> > convergence_parameter_objects;
    std::map<std::shared_ptr<const void>, std::string> source_code_for_convergence_parameter_objects;
    std::vector<std::shared_ptr<onerut_normal_operator::Eig> > eig_objects;
    std::map<std::shared_ptr<const void>, std::string> source_code_for_eig_objects;
    std::vector<std::shared_ptr<onerut_normal_operator::Mean> > mean_objects;
    std::map<std::shared_ptr<const void>, std::string> source_code_for_mean_objects;
    std::vector<std::shared_ptr<onerut_request::PrintValueRequest > > print_value_request_objects;
    std::map<std::shared_ptr<const void>, std::string> source_code_for_print_value_request_objects;
    // -------------------------------------------------------------------------
    for (const auto& ast_head_node : ats_head_nodes) {
        const auto add_convergence_parameter_objects = std::bind(
                add_if_type_matches<onerut_convergence_parameter::ConvergenceParameter>,
                std::ref(convergence_parameter_objects),
                std::ref(source_code_for_convergence_parameter_objects),
                std::placeholders::_1);
        dfs(ast_head_node, add_convergence_parameter_objects);
        const auto add_eig_objects = std::bind(
                add_if_type_matches<onerut_normal_operator::Eig>,
                std::ref(eig_objects),
                std::ref(source_code_for_eig_objects),
                std::placeholders::_1);
        dfs(ast_head_node, add_eig_objects);
        const auto add_mean_objects = std::bind(
                add_if_type_matches<onerut_normal_operator::Mean>,
                std::ref(mean_objects),
                std::ref(source_code_for_mean_objects),
                std::placeholders::_1);
        dfs(ast_head_node, add_mean_objects);
        const auto add_value_request_objects = std::bind(
                add_if_type_matches<onerut_request::PrintValueRequest>,
                std::ref(print_value_request_objects),
                std::ref(source_code_for_print_value_request_objects),
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
                << Aka(object, akas_for_convergence_parameter_objects, source_code_for_convergence_parameter_objects) << std::endl;
    }
    for (const auto& object : eig_objects) {
        std::cout << "[INVENTORY] " << "[EIG] "
                << Aka(object, akas_for_eig_objects, source_code_for_eig_objects)
                << std::endl;
    }
    for (const auto& object : mean_objects) {
        std::cout << "[INVENTORY] " << "[MEAN] "
                << Aka(object, akas_for_mean_objects, source_code_for_mean_objects)
                << std::endl;
    }
    for (const auto& object : print_value_request_objects) {
        std::cout << "[INVENTORY] " << "[PRINT VALUE REQUEST] "
                << Aka(object, akas_for_print_value_request_objects, source_code_for_print_value_request_objects)
                //<< ", only in summary: " << object->print_only_in_summary()
                << std::endl;
    }
    // -------------------------------------------------------------------------
    // check if every convergence_parameter_objects has set expression.
    // *************************************************************************
    // *************************************************************************    
    print_section_bar("DEPENDENCIES RESOLVER");

    for (const auto& object : convergence_parameter_objects) {
        std::cout << "[DEPENDENCIES] " << "[DEPENDABLE] "  << "[CONVERGENCE PARAMETER] "
                << Aka(object, akas_for_convergence_parameter_objects, source_code_for_convergence_parameter_objects) << std::endl;
        const auto dependences = onerut_dependence::dependence_list(dependence_is_convergence_parameter, object);
        const auto dependences_eig = dependence_filter_eig(dependences);
        const auto dependences_mean = dependence_filter_mean(dependences);
        std::cout << "dependence.size() =" << dependences.size() << std::endl;
        for (const auto dependence : dependences) {//DEBUG
            std::cout << dependence.lock() << " "; //DEBUG
        }//DEBUG
        std::cout << std::endl; //DEBUG
        for (const auto dependence : dependences_eig) {
            std::cout << "[DEPENDENCIES] " << "[DEPENDS ON] " << "[EIG] "
                    << Aka(dependence, akas_for_eig_objects, source_code_for_eig_objects)
                    << std::endl;
        }
        for (const auto dependence : dependences_mean) {
            std::cout << "[DEPENDENCIES] " << "[DEPENDS ON] " << "[MEAN] "
                    << Aka(dependence, akas_for_mean_objects, source_code_for_mean_objects)
                    << std::endl;
        }
        std::cout << std::endl;
    }

    // *************************************************************************
    // *************************************************************************    
    print_section_bar("SELF-CONSISTENT LOOP");
    // -------------------------------------------------------------------------    
    bool global_convergence = false;
    for (unsigned iteracja = 0; iteracja < n_max_iterations; ++iteracja) {
        std::cout << esc::manip::bg_yellow
                << "[DECLARATIVE MODE] [STEP] [SELF-CONSISTENT LOOP] [ITERATIONS] "
                << "iteration number " << std::setw(4) << iteracja << "."
                << esc::manip::reset
                << std::endl;
        for (const auto& eig : eig_objects) {
            std::cout << "[CALCULATIONS] [EIG ] "
                    << Aka(eig, akas_for_eig_objects, source_code_for_eig_objects)
                    << std::endl;
            eig->latch();
        }
        for (const auto& mean : mean_objects) {
            std::cout << "[CALCULATIONS] [MEAN] "
                    << Aka(mean, akas_for_mean_objects, source_code_for_mean_objects)
                    << std::endl;
            mean->latch();
        }
        for (const auto& convergence_parameter_object : convergence_parameter_objects) {
            std::cout << "[CALCULATIONS] [CONVERGENCE PARAMETER] "
                    << Aka(convergence_parameter_object, akas_for_convergence_parameter_objects, source_code_for_convergence_parameter_objects)
                    << std::endl;
            convergence_parameter_object->recalcuate();
        }
        for (const auto& request : print_value_request_objects) {
            if (request->print_only_in_summary()) {
                continue;
            }
            std::cout << "[PRINT VALUE REQUEST] "
                    << Aka(request, akas_for_print_value_request_objects, source_code_for_print_value_request_objects) << std::endl;
            request->print(std::cout, "[request] ");
        }
        //for (const auto& eig : eig_objects) {
        //    eig->reset();
        //}
        //for (const auto& mean : mean_objects) {
        //    mean->reset();
        //}
        for (const auto& object : convergence_parameter_objects) {
            double old_value = object->value_real();
            object->revolve();
            double new_value = object->value_real();
            std::cout << "[CONVERGENCE PARAMETER] [OLD VALUE => NEW VALUE] "
                    << Aka(object, akas_for_convergence_parameter_objects, source_code_for_convergence_parameter_objects) << " "
                    << old_value << " => " << new_value
                    << std::endl;
        }
        bool global_convergence_accumulator = true;
        for (const auto& object : convergence_parameter_objects) {
            const bool is_converged = object->is_converged();
            std::cout << "[CONVERGENCE PARAMETER] [CONVERGENCE TEST] ";
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
        std::cout << "[GLOBAL CONVERGENCE] " << esc::manip::green << "✓✓✓...✓✓" << esc::manip::reset;
    } else {
        std::cout << "[GLOBAL CONVERGENCE] " << esc::manip::red << "✘✘✘...✘✘" << esc::manip::reset;
    }
    std::cout << std::endl;
    for (const auto& request : print_value_request_objects) {
        std::cout << "[PRINT VALUE REQUEST] "
                << Aka(request, akas_for_print_value_request_objects, source_code_for_print_value_request_objects) << std::endl;
        request->print(std::cout, "[request] ");
    }
    // -------------------------------------------------------------------------
}