#include<iostream>
#include<iomanip>
#include<algorithm>
#include<functional>

#include<boost/range/adaptor/map.hpp>

#include<esc/esc_manip.hpp>
#include<string_utils/string_span.hpp>
#include<onerut_dependence/dependence_dfs.hpp>
#include<onerut_convergence_parameter/convergence_parameter.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_request/request_print_value.hpp>
#include<onerut/utility_ast_asset_dfs.hpp> // TODO will  be deleted!
#include<onerut/grep_ast_asset.hpp>
#include<onerut/grep_ref_container.hpp>
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

// -------------------------------------

struct DependablePresenter;

struct DependablePresenterFrame {
    DependablePresenterFrame(
            const DependablePresenter & presenter,
            const std::shared_ptr<const onerut_dependence::Dependable>& dependable);
    const DependablePresenter & _presenter;
    const std::shared_ptr<const onerut_dependence::Dependable>& _dependable;
};

DependablePresenterFrame::DependablePresenterFrame(
        const DependablePresenter & presenter,
        const std::shared_ptr<const onerut_dependence::Dependable>& dependable) :
_presenter(presenter),
_dependable(dependable) {
}

struct DependablePresenter {
    DependablePresenter(
            const Presenter< onerut_convergence_parameter::ConvergenceParameter>& presenter_for_convergence_parameter_objects,
            const Presenter< onerut_normal_operator::Eig>& presenter_for_eig_objects,
            const Presenter< onerut_normal_operator::Mean>& presenter_for_mean_objects,
            const Presenter< onerut_request::PrintValueRequest>& presenter_for_print_value_request_objects);
    DependablePresenterFrame operator()(std::shared_ptr<const onerut_dependence::Dependable> dependable) const;
    const Presenter< onerut_convergence_parameter::ConvergenceParameter>& _presenter_for_convergence_parameter_objects;
    const Presenter< onerut_normal_operator::Eig>& _presenter_for_eig_objects;
    const Presenter< onerut_normal_operator::Mean>& _presenter_for_mean_objects;
    const Presenter< onerut_request::PrintValueRequest>& _presenter_for_print_value_request_objects;
};

std::ostream& operator<<(std::ostream& stream, const DependablePresenterFrame& frame) {
    if (const auto& casted = std::dynamic_pointer_cast<const onerut_convergence_parameter::ConvergenceParameter>(frame._dependable)) {
        stream << "[CONVERGENCE PARAMETER] "
                << frame._presenter._presenter_for_convergence_parameter_objects(casted);
    }
    if (const auto& casted = std::dynamic_pointer_cast<const onerut_normal_operator::Eig>(frame._dependable)) {
        stream << "[EIG] "
                << frame._presenter._presenter_for_eig_objects(casted);
    }
    if (const auto& casted = std::dynamic_pointer_cast<const onerut_normal_operator::Mean>(frame._dependable)) {
        stream << "[MEAN] "
                << frame._presenter._presenter_for_mean_objects(casted);
    }
    if (const auto& casted = std::dynamic_pointer_cast<const onerut_request::PrintValueRequest>(frame._dependable)) {
        stream << "[REQUEST] "
                << frame._presenter._presenter_for_print_value_request_objects(casted);
    }
    return stream;
}

DependablePresenter::DependablePresenter(
        const Presenter<onerut_convergence_parameter::ConvergenceParameter>& presenter_for_convergence_parameter_objects,
        const Presenter<onerut_normal_operator::Eig>& presenter_for_eig_objects,
        const Presenter<onerut_normal_operator::Mean>& presenter_for_mean_objects,
        const Presenter<onerut_request::PrintValueRequest>& presenter_for_print_value_request_objects) :
_presenter_for_convergence_parameter_objects(presenter_for_convergence_parameter_objects),
_presenter_for_eig_objects(presenter_for_eig_objects),
_presenter_for_mean_objects(presenter_for_mean_objects),
_presenter_for_print_value_request_objects(presenter_for_print_value_request_objects) {
}

DependablePresenterFrame
DependablePresenter::operator()(std::shared_ptr<const onerut_dependence::Dependable> dependable) const {
    return DependablePresenterFrame(*this, dependable);
}

// -------------------------------------

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

std::vector<std::shared_ptr<const onerut_dependence::Dependable>>
dependence_filter_eig_mean(std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependences) {
    using MeanT = onerut_normal_operator::Mean;
    using EigT = onerut_normal_operator::Eig;
    std::vector<std::shared_ptr<const onerut_dependence::Dependable>> result;
    for (const auto& dependence : dependences) {
        const auto& dependence_shared = dependence.lock();
        assert(dependence_shared);
        if (std::dynamic_pointer_cast<const MeanT>(dependence_shared)) {
            result.push_back(dependence_shared);
        }
        if (std::dynamic_pointer_cast<const EigT>(dependence_shared)) {
            result.push_back(dependence_shared);
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
//
//template<class T>
//void
//add_if_type_matches(
//        std::vector<std::shared_ptr<T> >& objects,
//        //std::map<std::shared_ptr<const void>, std::string>& source_code_for_objects,
//        const onerut_parser_exec::onerut_ast::asset::AssetNode & asset_node) {
//    const auto asset = asset_node.asset;
//    const auto asset_deref = asset.deref();
//    if (asset_deref.is_either_value_or_type()) {
//        if (const auto &object = asset_deref.typed_value_or_empty<T>()) {
//            if (std::find(cbegin(objects), cend(objects), object) == cend(objects)) {
//                objects.push_back(*object);
//                //source_code_for_objects[*object] =
//                //        string_utils::to_string(asset_node.source->span);
//            }
//        }
//    }
//}

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
    const auto source_code_for_convergence_parameter_objects = grep_ast_asset<onerut_convergence_parameter::ConvergenceParameter>(ats_head_nodes);
    const auto source_code_for_eig_objects = grep_ast_asset<onerut_normal_operator::Eig>(ats_head_nodes);
    const auto source_code_for_mean_objects = grep_ast_asset<onerut_normal_operator::Mean>(ats_head_nodes);
    const auto source_code_for_print_value_request_objects = grep_ast_asset<onerut_request::PrintValueRequest>(ats_head_nodes);
    // -------------------------------------------------------------------------
    const auto akas_for_convergence_parameter_objects =
            grep_ref_container<onerut_convergence_parameter::ConvergenceParameter>();
    const auto akas_for_eig_objects =
            grep_ref_container<onerut_normal_operator::Eig>();
    const auto akas_for_mean_objects =
            grep_ref_container<onerut_normal_operator::Mean>();
    const auto akas_for_print_value_request_objects =
            grep_ref_container<onerut_request::PrintValueRequest>();
    // -------------------------------------------------------------------------
    Presenter<onerut_convergence_parameter::ConvergenceParameter> presenter_for_convergence_parameter_objects(
            akas_for_convergence_parameter_objects,
            source_code_for_convergence_parameter_objects);
    Presenter<onerut_normal_operator::Eig> presenter_for_eig_objects(
            akas_for_eig_objects,
            source_code_for_eig_objects);
    Presenter<onerut_normal_operator::Mean> presenter_for_mean_objects(
            akas_for_mean_objects,
            source_code_for_mean_objects);
    Presenter<onerut_request::PrintValueRequest> presenter_for_print_value_request_objects(
            akas_for_print_value_request_objects,
            source_code_for_print_value_request_objects);
    // -------------------------------------------------------------------------
    for (const auto& object : source_code_for_convergence_parameter_objects | boost::adaptors::map_keys) {
        std::cout << "[INVENTORY] " << "[CONVERGENCE PARAMETER] "
                << presenter_for_convergence_parameter_objects(object)
                << std::endl;
    }
    for (const auto& object : source_code_for_eig_objects | boost::adaptors::map_keys) {
        std::cout << "[INVENTORY] " << "[EIG] "
                << presenter_for_eig_objects(object)
                << std::endl;
    }
    for (const auto& object : source_code_for_mean_objects | boost::adaptors::map_keys) {
        std::cout << "[INVENTORY] " << "[MEAN] "
                << presenter_for_mean_objects(object)
                << std::endl;
    }
    for (const auto& object : source_code_for_print_value_request_objects | boost::adaptors::map_keys) {
        std::cout << "[INVENTORY] " << "[PRINT VALUE REQUEST] "
                << presenter_for_print_value_request_objects(object)
                //<< ", only in summary: " << object->print_only_in_summary()
                << std::endl;
    }
    // -------------------------------------------------------------------------
    // check if every convergence_parameter_objects has set expression.
    // *************************************************************************
    // *************************************************************************    
    print_section_bar("DEPENDENCIES RESOLVER");

    DependablePresenter presenter_for_dependable(
            presenter_for_convergence_parameter_objects,
            presenter_for_eig_objects,
            presenter_for_mean_objects,
            presenter_for_print_value_request_objects);
    for (const auto& object : source_code_for_convergence_parameter_objects | boost::adaptors::map_keys) {
        std::cout << "[DEPENDENCIES] " << "[DEPENDABLE] " << "[CONVERGENCE PARAMETER] "
                << presenter_for_convergence_parameter_objects(object)
                << std::endl;
        const auto dependences = onerut_dependence::dependence_list(dependence_is_convergence_parameter, object);
        const auto dependences_eig_mean = dependence_filter_eig_mean(dependences);
        for (const auto dependence : dependences_eig_mean) {
            std::cout << "[DEPENDENCIES] " << "[DEPENDS ON] "
                    << presenter_for_dependable(dependence)
                    << std::endl;
        }
        std::cout << std::endl;
    }

    for (const auto& object : source_code_for_print_value_request_objects | boost::adaptors::map_keys) {
        std::cout << "[DEPENDENCIES] " << "[DEPENDABLE] " << "[REQUEST] "
                << presenter_for_print_value_request_objects(object)
                << std::endl;
        const auto dependences = onerut_dependence::dependence_list(dependence_is_convergence_parameter, object);
        const auto dependences_eig_mean = dependence_filter_eig_mean(dependences);
        for (const auto dependence : dependences_eig_mean) {
            std::cout << "[DEPENDENCIES] " << "[DEPENDS ON] "
                    << presenter_for_dependable(dependence)
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
        for (const auto& object : source_code_for_eig_objects | boost::adaptors::map_keys) {
            std::cout << "[CALCULATIONS] [EIG ] "
                    << presenter_for_eig_objects(object)
                    << std::endl;
            object->latch();
        }
        for (const auto& object : source_code_for_mean_objects | boost::adaptors::map_keys) {
            std::cout << "[CALCULATIONS] [MEAN] "
                    << presenter_for_mean_objects(object)
                    << std::endl;
            object->latch();
        }
        for (const auto& object : source_code_for_convergence_parameter_objects | boost::adaptors::map_keys) {
            std::cout << "[CALCULATIONS] [CONVERGENCE PARAMETER] "
                    << presenter_for_convergence_parameter_objects(object)
                    << std::endl;
            object->recalcuate();
        }
        for (const auto& object : source_code_for_print_value_request_objects | boost::adaptors::map_keys) {
            if (object->print_only_in_summary()) {
                continue;
            }
            std::cout << "[PRINT VALUE REQUEST] "
                    << presenter_for_print_value_request_objects(object)
                    << std::endl;
            object->print(std::cout, "[request] ");
        }
        for (const auto& object : source_code_for_convergence_parameter_objects | boost::adaptors::map_keys) {
            double old_value = object->value_real();
            object->revolve();
            double new_value = object->value_real();
            std::cout << "[CONVERGENCE PARAMETER] [OLD VALUE => NEW VALUE] "
                    << presenter_for_convergence_parameter_objects(object) << " "
                    << old_value << " => " << new_value
                    << std::endl;
        }
        bool global_convergence_accumulator = true;
        for (const auto& object : source_code_for_convergence_parameter_objects | boost::adaptors::map_keys) {
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
    for (const auto& object : source_code_for_print_value_request_objects | boost::adaptors::map_keys) {
        std::cout << "[PRINT VALUE REQUEST] "
                << presenter_for_print_value_request_objects(object)
                << std::endl;
        object->print(std::cout, "[request] ");
    }
    // -------------------------------------------------------------------------
}
