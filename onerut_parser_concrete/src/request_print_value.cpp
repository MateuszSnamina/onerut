#include<cassert>
#include<memory>

#include<string_utils/greek_support.hpp>
#include<onerut_normal_operator/to_string.hpp>
#include<onerut_parser_concrete/request_print_value.hpp>

namespace onerut_parser {

    // *************************************************************************

    PrintValueRequestTyped<onerut_parser::CompileError>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_parser::CompileError>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix
                << "[value] " << "error message = " << instance->what()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_scalar::Integer>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_scalar::Integer>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix
                << "[value] " << "value = " << instance->value_integer()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_scalar::Real>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_scalar::Real>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix
                << "[value] " << "value = " << instance->value_real()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_scalar::Complex>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_scalar::Complex>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix
                << "[value] " << "value = " << instance->value_complex()
                << std::endl;
    }


    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::CustomDomain>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_normal_operator::CustomDomain>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->size()
                << std::endl;
        stream << line_prefix << "[value] "
                << "states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::OscillatorDomain>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_normal_operator::OscillatorDomain>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->size()
                << std::endl;
        stream << line_prefix << "[value] "
                << "vibronic states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::SpinDomain>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_normal_operator::SpinDomain>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->n_max_stars
                << std::endl;
        stream << line_prefix << "[value] "
                << "multiplicity = " << instance->multiplicity
                << std::endl;
        stream << line_prefix << "[value] "
                << "spin states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::KronDomain>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_normal_operator::KronDomain>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "dimension = " << instance->size()
                << std::endl;
        stream << line_prefix << "[value] "
                << "kron states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*instance))
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::StateIndex>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_normal_operator::StateIndex>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "value = " << instance->to_str()
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::KronPlaceholder>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_normal_operator::KronPlaceholder>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "place = " << instance->place
                << std::endl;
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::AbstractRealOperator>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_normal_operator::AbstractRealOperator>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << onerut_normal_operator::to_string(*instance, line_prefix + "[value] "); //TODO to_string change to operator<<
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::Eig>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_normal_operator::Eig>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << onerut_normal_operator::to_string(*instance, line_prefix + "[value] "); //TODO to_string change to operator<<
    }

    // *************************************************************************

    PrintValueRequestTyped<onerut_normal_operator::Mean>::PrintValueRequestTyped(std::shared_ptr<Type> instance) :
    instance(instance) {
        assert(instance);
    }

    void PrintValueRequestTyped<onerut_normal_operator::Mean>::print(std::ostream& stream, std::string line_prefix) const {
        assert(instance);
        stream << line_prefix << "[value] "
                << "value = " << instance->value_real()
                << std::endl;
    }

    // *************************************************************************
}
