#include<cassert>
#include<memory>

#include<string_utils/greek_support.hpp>
#include<onerut_normal_operator/to_string.hpp>
#include<onerut_request/request_print_value.hpp>

namespace onerut_request {

    PrintValueRequest::PrintValueRequest(bool print_only_in_summary) :
    _print_only_in_summary(print_only_in_summary) {

    }

    bool PrintValueRequest::print_only_in_summary() const {
        return _print_only_in_summary;
    }

    // *************************************************************************

    //    PrintValueRequestTyped<onerut_parser_exec::CompileError>::PrintValueRequestTyped(
    //      std::shared_ptr<Type> instance,
    //      bool print_only_in_summary) :
    //    PrintValueRequest(print_only_in_summary),    
    //    instance(instance) {
    //        assert(instance);
    //    }
    //
    //    void PrintValueRequestTyped<onerut_parser_exec::CompileError>::print(
    //         std::ostream& stream,
    //         std::string line_prefix) const {
    //        assert(instance);
    //        stream << line_prefix
    //                << "[value] " << "error message = " << instance->what()
    //                << std::endl;
    //    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_scalar::Integer>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_scalar::Integer>::dependence() const {
        return {instance};
    }

    void
    PrintValueRequestTyped<onerut_scalar::Integer>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix
                << "[value] " << "value = " << instance->value_integer()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_scalar::Real>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_scalar::Real>::dependence() const {
        return {instance};
    }

    void
    PrintValueRequestTyped<onerut_scalar::Real>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix
                << "[value] " << "value = " << instance->value_real()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_scalar::Complex>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_scalar::Complex>::dependence() const {
        return {instance};
    }

    void
    PrintValueRequestTyped<onerut_scalar::Complex>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix
                << "[value] " << "value = " << instance->value_complex()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_env::Env>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_env::Env>::dependence() const {
        return {instance};
    }

    void
    PrintValueRequestTyped<onerut_env::Env>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix
                << "[value] " << "value = " << instance->value_real()
                << std::endl;
        stream << line_prefix
                << "[env-variable name] " << "value = " << instance->env_variable_name()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_convergence_parameter::ConvergenceParameter>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_convergence_parameter::ConvergenceParameter>::dependence() const {
        return {instance};
    }

    void
    PrintValueRequestTyped<onerut_convergence_parameter::ConvergenceParameter>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix
                << "[value] " << "parameter (exposed value) = " << instance->value_real()
                << std::endl;
        if (instance->expression()) {
            stream << line_prefix << "[value] " << "expression value = " << instance->expression()->value_real()
                    << std::endl;
        } else {
            stream << line_prefix << "[value] " << "expression has not been set yet."
                    << std::endl;
        }
        stream << line_prefix << "[value] " << "threshold = " << instance->threshold()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::CustomDomain>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::CustomDomain>::dependence() const {
        return {};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::CustomDomain>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->size()
                << std::endl;
        stream << line_prefix << "[value] "
                << "states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::OscillatorDomain>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::OscillatorDomain>::dependence() const {
        return {};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::OscillatorDomain>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->size()
                << std::endl;
        stream << line_prefix << "[value] "
                << "vibronic states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::SpinDomain>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::SpinDomain>::dependence() const {
        return {};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::SpinDomain>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->size()//n_max_stars
                << std::endl;
        stream << line_prefix << "[value] "
                << "multiplicity = " << instance->multiplicity
                << std::endl;
        stream << line_prefix << "[value] "
                << "spin states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::EgDomain>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::EgDomain>::dependence() const {
        return {};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::EgDomain>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->size()
                << std::endl;
        stream << line_prefix << "[value] "
                << "eg states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }
    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::FockDomain>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::FockDomain>::dependence() const {
        return {};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::FockDomain>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->size()
                << std::endl;
        stream << line_prefix << "[value] "
                << "n_particles = " << instance->n_particles
                << std::endl;
        stream << line_prefix << "[value] "
                << "n_orbitals = " << instance->orbital_names.size()
                << std::endl;
        stream << line_prefix << "[value] "
                << "fock states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::KronDomain>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::KronDomain>::dependence() const {
        return {};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::KronDomain>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->size()
                << std::endl;
        stream << line_prefix << "[value] "
                << "kron states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::StateIndex>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::StateIndex>::dependence() const {
        return {};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::StateIndex>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "value = " << instance->to_str()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::OrbitalIndex>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::OrbitalIndex>::dependence() const {
        return {};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::OrbitalIndex>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "orbital index = " << instance->index
                << std::endl;
        stream << line_prefix << "[value] "
                << "orbital name = " << instance->fetch_name()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::KronPlaceholder>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::KronPlaceholder>::dependence() const {
        return {};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::KronPlaceholder>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "place = " << instance->place
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::AbstractRealOperator>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::AbstractRealOperator>::dependence() const {
        return {instance};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::AbstractRealOperator>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << onerut_normal_operator::to_string(*instance, line_prefix + "[value] "); //TODO to_string change to operator<<
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::Eig>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::Eig>::dependence() const {
        return {instance};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::Eig>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << onerut_normal_operator::to_string(*instance, line_prefix + "[value] "); //TODO to_string change to operator<<
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::Mean>::PrintValueRequestTyped(
            std::shared_ptr<Type> instance,
            bool print_only_in_summary) :
    PrintValueRequest(print_only_in_summary),
    instance(instance) {
        assert(instance);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    PrintValueRequestTyped<onerut_normal_operator::Mean>::dependence() const {
        return {instance};
    }

    void
    PrintValueRequestTyped<onerut_normal_operator::Mean>::print(
            std::ostream& stream,
            std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "value = " << instance->value_real()
                << std::endl;
    }

    // *************************************************************************
}
