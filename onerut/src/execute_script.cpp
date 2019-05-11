#include<iostream>
#include<iomanip>
#include<algorithm>
#include<iterator>
#include<functional>

#include<boost/range/adaptor/map.hpp>
#include <boost/range/adaptor/reversed.hpp>

#include<boost/graph/adjacency_list.hpp>
//#include<boost/property_map/transform_value_property_map.hpp>
#include<boost/graph/graphviz.hpp>
#include<boost/graph/topological_sort.hpp>

#include<esc/esc_manip.hpp>
#include<string_utils/string_span.hpp>
#include<onerut_dependence/dependence_dfs.hpp>
#include<onerut_convergence_parameter/convergence_parameter.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_request/request_print_value.hpp>
#include<onerut/presenter.hpp>
#include<onerut/presenter_dependable.hpp>
#include<onerut/grep_ast_asset.hpp>
#include<onerut/grep_ref_container.hpp>
#include<onerut/line_preprocessor.hpp>
#include<onerut/line_processor.hpp>
#include<onerut/execute_script.hpp>

/*
struct Person {
    std::string name;
    int id;
};

struct Edge {

    Edge(int i) : id(i) {
    };
    int id;
};

//bool operator<(const Person& person1, const Person& person2) {
//    return person1.name < person2.name;
//}

bool operator==(const Person& person1, const Person& person2) {
    return person1.name == person2.name && person1.id == person2.id;
}

std::ostream& operator<<(std::ostream& stream, const Person& person) {
    stream << "MyPersonPrint:" << person.name << person.id;
    return stream;
}

class DepencenciesGrap_lesson {
public:

    DepencenciesGrap_lesson() {
        typedef boost::adjacency_list<boost::setS, boost::vecS, boost::directedS, Person> GraphBglT;
        GraphBglT graph;
        Person p1{"aa", 11};
        Person p2{"bb", 22};
        Person p3{"aa", 11};
        const auto v1 = boost::add_vertex(p1, graph);
        const auto v2 = boost::add_vertex(p2, graph);

        typedef boost::graph_traits<GraphBglT>::vertex_iterator VertexIteratorBglT;
        typedef boost::graph_traits<GraphBglT>::vertex_descriptor VertexDescriptorBglT;
        typedef boost::graph_traits<GraphBglT>::edge_descriptor EdgeDescriptorBglT;

        std::pair<VertexIteratorBglT, VertexIteratorBglT> vertices_begin_end = boost::vertices(graph);
        VertexIteratorBglT it = std::find_if(vertices_begin_end.first, vertices_begin_end.second,
                [&graph, &p3](const VertexDescriptorBglT & run_vertex_descriptor) {
                    std::cout << "check ";
                    return graph[run_vertex_descriptor] == p3;
                    //                    return false;
                });
        if (it != vertices_begin_end.second) {
            std::cout << "already added" << std::endl;
        } else {
            std::cout << "not already added" << std::endl;
        }
        //const auto v3 = boost::add_vertex(p1, graph);

        const std::pair<EdgeDescriptorBglT, bool> result = boost::add_edge(v1, v2, graph);
        assert(result.second);
        std::cout << "edgeDesc: "
                << graph[boost::source(result.first, graph)] << "--->"
                << graph[boost::target(result.first, graph)] << std::endl;
        const std::pair<EdgeDescriptorBglT, bool> result_re = boost::add_edge(v1, v1, graph);
        assert(result_re.second);
        std::cout << "edgeDesc: "
                << graph[boost::source(result_re.first, graph)] << "--->"
                << graph[boost::target(result_re.first, graph)] << std::endl;
        assert(result.first != result_re.first);

        boost::dynamic_properties dp;
        dp.property("node_id", boost::get(&Person::name, graph));
        dp.property("node_id1", boost::get(&Person::id, graph));
        boost::write_graphviz_dp(std::cout, graph, dp);

        auto xxx = boost::get(&Person::name, graph);
        std::cout << xxx[v1] << std::endl;
        std::cout << graph[v1] << std::endl;
        std::cout << graph[v1].id << std::endl;

        std::cout << "----------" << std::endl;



        try {
            typedef std::vector< VertexDescriptorBglT > container;
            container c;

            boost::topological_sort(graph, std::back_inserter(c));
            boost::write_graphviz(std::cout, graph);

            std::cout << "A topological ordering: ";
            for (container::reverse_iterator ii = c.rbegin(); ii != c.rend(); ++ii) {
                std::cout << xxx(*ii) << " ";
                std::cout << graph[*ii] << " ";
            }
            std::cout << std::endl;
        } catch (const boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::not_a_dag> >& ex) {
            std::cerr << "Topological sort failed as dependencies graph in not a dag." << std::endl;
        }

        std::cout << "----------" << std::endl;

        boost::adjacency_list<boost::setS, boost::setS, boost::directedS, Person, Edge> graph1;

        const auto v11 = boost::add_vertex(p1, graph1);
        const auto v12 = boost::add_vertex(p2, graph1);

        boost::add_edge(v11, v12, Edge(666), graph1);

        boost::dynamic_properties dp3;
        dp3.property("node_id", boost::get(&Person::name, graph1));
        dp3.property("node_id1", boost::get(&Person::id, graph1));
        dp3.property("edge_id1", boost::get(&Edge::id, graph1));
        boost::write_graphviz_dp(std::cout, graph1, dp3);

    }
};
 */

class DependenciesGraph {
public:
    using StoredT = std::shared_ptr<const onerut_dependence::Dependable>;
    using GraphBglT = boost::adjacency_list<boost::setS, boost::vecS, boost::directedS, StoredT>;
    using VertexDescriptorBglT = boost::graph_traits<GraphBglT>::vertex_descriptor;
    using VertexIteratorBglT = boost::graph_traits<GraphBglT>::vertex_iterator;
    using EdgeDescriptorBglT = boost::graph_traits<GraphBglT>::edge_descriptor;
    using EdgeIteratorBglT = boost::graph_traits<GraphBglT>::edge_iterator;

    GraphBglT _graph;

    DependenciesGraph() :
    _graph() {
    }

    const GraphBglT& graph() const {
        return _graph;
    }

    VertexDescriptorBglT add_vertex_if_not_added(const StoredT& vertex) {
        const std::pair<VertexIteratorBglT, VertexIteratorBglT> vertices_begin_end =
                boost::vertices(_graph);
        VertexIteratorBglT it =
                std::find_if(
                vertices_begin_end.first, vertices_begin_end.second,
                [this, &vertex](const VertexDescriptorBglT & run_vertex_descriptor) {
                    return this->_graph[run_vertex_descriptor] == vertex;
                });
        if (it != vertices_begin_end.second) {
            //std::cout << "already added" << std::endl;
            assert(_graph[*it] == vertex);
            return *it;
        }
        //std::cout << "not already added, adding now" << std::endl;
        const VertexDescriptorBglT verted_descriptor = boost::add_vertex(vertex, _graph);
        assert(_graph[verted_descriptor] == vertex);
        return verted_descriptor;
    }

    EdgeDescriptorBglT add_dependence(const StoredT& source, const StoredT& target) {
        const VertexDescriptorBglT source_vertex_descriptor =
                add_vertex_if_not_added(source);
        const VertexDescriptorBglT target_vertex_descriptor =
                add_vertex_if_not_added(target);
        assert(_graph[source_vertex_descriptor] == source);
        assert(_graph[target_vertex_descriptor] == target);
        const std::pair<EdgeDescriptorBglT, bool> result = boost::add_edge(
                source_vertex_descriptor,
                target_vertex_descriptor,
                _graph);
        const EdgeDescriptorBglT& edge_descriptor = result.first;
        const bool& success = result.second;
        assert(success);
        assert(boost::source(edge_descriptor, _graph) == source_vertex_descriptor);
        assert(boost::target(edge_descriptor, _graph) == target_vertex_descriptor);
        return edge_descriptor;
    }

    void write_graphviz(std::ostream& stream) const {
        // https://stackoverflow.com/questions/46857868/using-boost-graph-library-with-a-custom-class-for-vertices
        const auto bundle = get(boost::vertex_bundle, _graph);
        boost::dynamic_properties dp;
        dp.property("node_id", make_transform_value_property_map(std::mem_fn(&StoredT::get), bundle));
        boost::write_graphviz_dp(stream, _graph, dp);
    }

    std::vector<VertexDescriptorBglT> calculate_execution_order() const {
        std::vector< VertexDescriptorBglT > execution_order;
        try {
            boost::topological_sort(_graph, std::back_inserter(execution_order));
        } catch (const boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::not_a_dag> >& ex) {
            std::cerr << "Topological sort failed as dependencies graph in not a dag." << std::endl;
        }
        return execution_order;
    }

    template<class Presenter>
    void print_topological_order(
            std::ostream& stream,
            const Presenter& presenter,
            const std::vector<VertexDescriptorBglT> & execution_order) const {
        const auto topological_order = execution_order | boost::adaptors::reversed;
        stream << "[TOPOLOGICAL ORDER] "
                << "The topological ordering: "
                << std::endl;

        for (const VertexDescriptorBglT & vertex_descriptor : topological_order) {
            stream << "[TOPOLOGICAL ORDER] "
                    << presenter(_graph[vertex_descriptor]) << " "
                    << std::endl;
        }
    }

    void execute_in_execution_order(
            const std::vector<VertexDescriptorBglT> & execution_order,
            std::function< void(const StoredT&) > executor) const {
        for (const VertexDescriptorBglT & vertex_descriptor : execution_order) {
            //std::cout << "[EXECUTE] " << std::endl;
            executor(_graph[vertex_descriptor]);
        }
    }
};

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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

// #############################################################################
// ############    execute_imperative_script    ################################
// #############################################################################

void
execute_imperative_script(
        const std::vector<std::shared_ptr<const std::string>>&lines) {
    process_imperative_lines(preprocess_line(lines));
}

// #############################################################################
// ############    execute_declarative_script    ###############################
// #############################################################################

void
execute_declarative_script(
        const std::vector<std::shared_ptr<const std::string>>&lines,
        unsigned n_max_iterations) {

    //DepencenciesGrap_lesson();
    //exit(1);

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
    const auto source_code_for_convergence_parameter_objects =
            grep_ast_asset<onerut_convergence_parameter::ConvergenceParameter>(ats_head_nodes);
    const auto source_code_for_eig_objects =
            grep_ast_asset<onerut_normal_operator::Eig>(ats_head_nodes);
    const auto source_code_for_mean_objects =
            grep_ast_asset<onerut_normal_operator::Mean>(ats_head_nodes);
    const auto source_code_for_print_value_request_objects =
            grep_ast_asset<onerut_request::PrintValueRequest>(ats_head_nodes);
    // -------------------------------------------------------------------------
    const auto grepped_convergence_parameter_objects =
            source_code_for_convergence_parameter_objects | boost::adaptors::map_keys;
    const auto grepped_eig_objects =
            source_code_for_eig_objects | boost::adaptors::map_keys;
    const auto grepped_mean_objects =
            source_code_for_mean_objects | boost::adaptors::map_keys;
    const auto grepped_print_value_request_objects =
            source_code_for_print_value_request_objects | boost::adaptors::map_keys;
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
    const auto presenter_for_convergence_parameter_objects = make_presenter(
            akas_for_convergence_parameter_objects,
            source_code_for_convergence_parameter_objects);
    const auto presenter_for_eig_objects = make_presenter(
            akas_for_eig_objects,
            source_code_for_eig_objects);
    const auto presenter_for_mean_objects = make_presenter(
            akas_for_mean_objects,
            source_code_for_mean_objects);
    const auto presenter_for_print_value_request_objects = make_presenter(
            akas_for_print_value_request_objects,
            source_code_for_print_value_request_objects);
    // -------------------------------------------------------------------------
    for (const auto& object_w : grepped_convergence_parameter_objects) {
        assert(!object_w.expired());
        const auto object = object_w.lock();
        std::cout << "[INVENTORY111] " << "[CONVERGENCE PARAMETER] "
                << presenter_for_convergence_parameter_objects(object)
                << std::endl;
    }
    for (const auto& object_w : grepped_eig_objects) {
        assert(!object_w.expired());
        const auto object = object_w.lock();
        std::cout << "[INVENTORY] " << "[EIG] "
                << presenter_for_eig_objects(object)
                << std::endl;
    }
    for (const auto& object_w : grepped_mean_objects) {
        assert(!object_w.expired());
        const auto object = object_w.lock();
        std::cout << "[INVENTORY] " << "[MEAN] "
                << presenter_for_mean_objects(object)
                << std::endl;
    }
    for (const auto& object_w : grepped_print_value_request_objects) {
        assert(!object_w.expired());
        const auto object = object_w.lock();
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
    // -------------------------------------------------------------------------
    DependablePresenter presenter_for_dependable(
            presenter_for_convergence_parameter_objects,
            presenter_for_eig_objects,
            presenter_for_mean_objects,
            presenter_for_print_value_request_objects);
    // -------------------------------------------------------------------------
    /*onerut_dependence::*/DependenciesGraph dependencies_graph;
    // -------------------------------------------------------------------------    
    for (const auto& dependable_w : grepped_convergence_parameter_objects) {
        assert(!dependable_w.expired());
        const auto dependable = dependable_w.lock();
        std::cout << "[DEPENDENCIES] " << "[DEPENDABLE] "
                << presenter_for_dependable(dependable)
                << std::endl;
        const auto dependences =
                onerut_dependence::unique_dependence_list(dependence_is_convergence_parameter, dependable);
        const auto dependences_eig_mean =
                dependence_filter_eig_mean(dependences);
        for (const auto dependence : dependences_eig_mean) {
            std::cout << "[DEPENDENCIES] " << "[DEPENDS ON] "
                    << presenter_for_dependable(dependence)
                    << std::endl;
            dependencies_graph.add_dependence(dependable, dependence);
        }
    }
    for (const auto& dependable_w : grepped_print_value_request_objects) {
        assert(!dependable_w.expired());
        const auto dependable = dependable_w.lock();
        std::cout << "[DEPENDENCIES] " << "[DEPENDABLE] "
                << presenter_for_dependable(dependable)
                << std::endl;
        const auto dependences
                = onerut_dependence::unique_dependence_list(dependence_is_convergence_parameter, dependable);
        const auto dependences_eig_mean
                = dependence_filter_eig_mean(dependences);
        for (const auto dependence : dependences_eig_mean) {
            std::cout << "[DEPENDENCIES] " << "[DEPENDS ON] "
                    << presenter_for_dependable(dependence)
                    << std::endl;
            if (!dependable->print_only_in_summary()) {
                dependencies_graph.add_dependence(dependable, dependence);
            }
        }
    }
    for (const auto& dependable_w : grepped_eig_objects) {
        assert(!dependable_w.expired());
        const auto dependable = dependable_w.lock();
        std::cout << "[DEPENDENCIES] " << "[DEPENDABLE] "
                << presenter_for_dependable(dependable)
                << std::endl;
        const auto dependences
                = onerut_dependence::unique_dependence_list(dependence_is_convergence_parameter, dependable);
        const auto dependences_eig_mean
                = dependence_filter_eig_mean(dependences);
        for (const auto dependence : dependences_eig_mean) {
            std::cout << "[DEPENDENCIES] " << "[DEPENDS ON] "
                    << presenter_for_dependable(dependence)
                    << std::endl;
            dependencies_graph.add_dependence(dependable, dependence);
        }
    }
    for (const auto& dependable_w : grepped_mean_objects) {
        assert(!dependable_w.expired());
        const auto dependable = dependable_w.lock();
        std::cout << "[DEPENDENCIES] " << "[DEPENDABLE] "
                << presenter_for_dependable(dependable)
                << std::endl;
        const auto dependences
                = onerut_dependence::unique_dependence_list(dependence_is_convergence_parameter, dependable);
        const auto dependences_eig_mean
                = dependence_filter_eig_mean(dependences);
        for (const auto dependence : dependences_eig_mean) {
            std::cout << "[DEPENDENCIES] " << "[DEPENDS ON] "
                    << presenter_for_dependable(dependence)
                    << std::endl;
            dependencies_graph.add_dependence(dependable, dependence);
        }
    }
    // -------------------------------------------------------------------------    
    dependencies_graph.write_graphviz(std::cout);
    // -------------------------------------------------------------------------    
    const auto execution_order = dependencies_graph.calculate_execution_order();
    // -------------------------------------------------------------------------    
    dependencies_graph.print_topological_order(std::cout, presenter_for_dependable, execution_order);
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
        for (const auto& object_w : grepped_eig_objects) {
            assert(!object_w.expired());
            const auto object = object_w.lock();
            std::cout << "[CALCULATIONS] [EIG ] "
                    << presenter_for_eig_objects(object)
                    << std::endl;
            object->latch();
        }
        for (const auto& object_w : grepped_mean_objects) {
            assert(!object_w.expired());
            const auto object = object_w.lock();
            std::cout << "[CALCULATIONS] [MEAN] "
                    << presenter_for_mean_objects(object)
                    << std::endl;
            object->latch();
        }
        for (const auto& object_w : grepped_convergence_parameter_objects) {
            assert(!object_w.expired());
            const auto object = object_w.lock();
            std::cout << "[CALCULATIONS] [CONVERGENCE PARAMETER] "
                    << presenter_for_convergence_parameter_objects(object)
                    << std::endl;
            object->recalcuate();
        }
        for (const auto& object_w : grepped_print_value_request_objects) {
            assert(!object_w.expired());
            const auto object = object_w.lock();
            if (object->print_only_in_summary()) {
                continue;
            }
            std::cout << "[PRINT VALUE REQUEST] "
                    << presenter_for_print_value_request_objects(object)
                    << std::endl;
            object->print(std::cout, "[request] ");
        }
        for (const auto& object_w : grepped_convergence_parameter_objects) {
            assert(!object_w.expired());
            const auto object = object_w.lock();
            double old_value = object->value_real();
            object->revolve();
            double new_value = object->value_real();
            std::cout << "[CONVERGENCE PARAMETER] [OLD VALUE => NEW VALUE] "
                    << presenter_for_convergence_parameter_objects(object) << " "
                    << old_value << " => " << new_value
                    << std::endl;
        }
        bool global_convergence_accumulator = true;
        for (const auto& object_w : grepped_convergence_parameter_objects) {
            assert(!object_w.expired());
            const auto object = object_w.lock();
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
    for (const auto& object_w : grepped_print_value_request_objects) {
        assert(!object_w.expired());
        const auto object = object_w.lock();
        std::cout << "[PRINT VALUE REQUEST] "
                << presenter_for_print_value_request_objects(object)
                << std::endl;
        object->print(std::cout, "[request] ");
    }
    // -------------------------------------------------------------------------
}
