#ifndef ONERUT_PARSER_ASSET_RECEIPT
#define ONERUT_PARSER_ASSET_RECEIPT

#include<esc/esc_manip.hpp>
#include<string_utils/greek_support.hpp>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/diagonalizator.hpp>
#include<onerut_normal_operator/to_string.hpp>

#include<onerut_parser/asset.hpp>
#include<onerut_parser/imperative_request.hpp>
#include<onerut_parser/asset_utility.hpp>

#include<onerut_parser/asset_receipt.hpp>

#include<string_utils/greek_support.hpp>

namespace onerut_parser {

    void print_receipt(std::ostream& stream, const Asset& asset, std::string line_prefix) {
        // ---------------------------------------------------------------------
        if (onerut_parser::utility::is_unset_ref(asset)) {
            stream << line_prefix << "[ref] "
                    << "Asset is an " << esc::manip::italic << "unset reference" << esc::manip::reset << "."
                    << std::endl;
            const auto result_reference = *(asset.reference_or_empty());
            stream << line_prefix << "[ref] "
                    << "reference name = " << string_utils::StreamToGreek(result_reference->get_name())
                    << std::endl;
        } else if (onerut_parser::utility::is_const_ref(asset)) {
            stream << line_prefix << "[ref] "
                    << "Asset is a " << esc::manip::italic << "const reference" << esc::manip::reset << "."
                    << std::endl;
            const auto result_reference = *(asset.reference_or_empty());
            stream << line_prefix << "[ref] "
                    << "reference name = " << string_utils::StreamToGreek(result_reference->get_name())
                    << std::endl;
        } else if (onerut_parser::utility::is_not_const_ref(asset)) {
            stream << line_prefix << "[ref] "
                    << "Asset is a " << esc::manip::italic << "not const reference" << esc::manip::reset << "."
                    << std::endl;
            const auto result_reference = *(asset.reference_or_empty());
            stream << line_prefix << "[ref] "
                    << "reference name = " << string_utils::StreamToGreek(result_reference->get_name())
                    << std::endl;
        } else {
            stream << line_prefix << "[ref] " << "Asset is not a reference." << std::endl;
        }

        // ---------------------------------------------------------------------
        if (asset.deref().is_empty()) {
            stream << line_prefix << "[deref] "
                    << "Asset-deref is an " << esc::manip::italic << "empty asset" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_parser::ExecRequest>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is an " << esc::manip::italic << "exec-request" << esc::manip::reset << " imperative injection."
                    << std::endl;
        } else if (asset.deref().is_compile_error()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is an " << esc::manip::italic << "error" << esc::manip::reset << "."
                    << std::endl;
            const auto error = *asset.deref().compile_error_or_empty();
            stream << line_prefix << "[deref] "
                    << "error message = " << error->what() << std::endl;
        } else if (asset.deref().is_given_type<onerut_scalar::Integer>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is an " << esc::manip::italic << "integer-number" << esc::manip::reset << "."
                    << std::endl;
            const auto result_integer = *(asset.deref().typed_value_or_empty<onerut_scalar::Integer>());
            stream << line_prefix << "[deref] " << "value = " << result_integer->value_integer() << std::endl;
        } else if (asset.deref().is_given_type<onerut_scalar::Real>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is a " << esc::manip::italic << "real-number" << esc::manip::reset << "."
                    << std::endl;
            const auto result_real = *(asset.deref().typed_value_or_empty<onerut_scalar::Real>());
            stream << line_prefix << "[deref] "
                    << "value = " << result_real->value_real()
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_scalar::Complex>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is a " << esc::manip::italic << "complex-number" << esc::manip::reset << "."
                    << std::endl;
            const auto result_complex = *(asset.deref().typed_value_or_empty<onerut_scalar::Complex>());
            stream << line_prefix << "[deref] "
                    << "value = " << result_complex->value_complex()
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::StateIndex>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is a " << esc::manip::italic << "normal-domain-state-index" << esc::manip::reset << "."
                    << std::endl;
            const auto state = *(asset.deref().typed_value_or_empty<onerut_normal_operator::StateIndex>());
            stream << line_prefix << "[deref] "
                    << "value = " << state->to_str()
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::Domain>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is a " << esc::manip::italic << "normal-domain" << esc::manip::reset << "."
                    << std::endl;
            const auto domain = *(asset.deref().typed_value_or_empty<onerut_normal_operator::Domain>());
            stream << line_prefix << "[deref] "
                    << "dimension = " << domain->state_names.size()
                    << std::endl;
            stream << line_prefix << "[deref] "
                    << "states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*domain))
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::OscillatorDomain>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is a " << esc::manip::italic << "oscillator-type-normal-domain" << esc::manip::reset << "."
                    << std::endl;
            const auto domain = *(asset.deref().typed_value_or_empty<onerut_normal_operator::OscillatorDomain>());
            stream << line_prefix << "[deref] "
                    << "dimension = " << domain->state_names.size()
                    << std::endl;
            stream << line_prefix << "[deref] "
                    << "states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*domain))
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::SpinDomain>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is a " << esc::manip::italic << "spin-type-normal-domain" << esc::manip::reset << "."
                    << std::endl;
            const auto domain = *(asset.deref().typed_value_or_empty<onerut_normal_operator::SpinDomain>());
            stream << line_prefix << "[deref] "
                    << "dimension = " << domain->n_max_stars
                    << std::endl;
            stream << line_prefix << "[deref] "
                    << "multiplicity = " << domain->multiplicity
                    << std::endl;
            stream << line_prefix << "[deref] "
                    << "states = " << string_utils::StreamToGreek(onerut_normal_operator::to_string(*domain))
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::AbstractOperator>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is a " << esc::manip::italic << "normal-domain-operator" << esc::manip::reset << "."
                    << std::endl;
            const auto op = *(asset.deref().typed_value_or_empty<onerut_normal_operator::AbstractOperator>());
            stream << onerut_normal_operator::to_string(*op, line_prefix + "[deref] "); //TODO to_string change to operator<<
        } else if (asset.deref().is_given_type<onerut_normal_operator::Eigs>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is " << esc::manip::italic << "normal-domain-eigs" << esc::manip::reset << "."
                    << std::endl;
            const auto eigs = *(asset.deref().typed_value_or_empty<onerut_normal_operator::Eigs>());
            stream << onerut_normal_operator::to_string(*eigs, line_prefix + "[deref] "); //TODO to_string change to operator<<
        } else if (asset.deref().is_given_type<onerut_normal_operator::Mean>()) {
            stream << line_prefix << "[deref] "
                    << "Asset-defer is " << esc::manip::italic << "normal-domain-mean" << esc::manip::reset << "."
                    << std::endl;
            const auto mean = *(asset.deref().typed_value_or_empty<onerut_normal_operator::Mean>());
            stream << line_prefix << "[deref] "
                    << "value = " << mean->value_real()
                    << std::endl;
        } else {
            stream << line_prefix << "[deref] "
                    << "Asset-defer type is not supported by receipt."
                    << std::endl;
        }



        // ---------------------------------------------------------------------
    }

}

#endif