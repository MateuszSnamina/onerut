#ifndef ONERUT_PARSER_ASSET_RECEIPT
#define ONERUT_PARSER_ASSET_RECEIPT

#include<esc/esc_manip.hpp>
#include<string_utils/greek_support.hpp>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_convergence_parameter/convergence_parameter.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_normal_operator/to_string.hpp>

#include<onerut_parser_exec/asset.hpp>
#include<onerut_parser_exec/asset_utility.hpp>
#include<onerut_request/request_imperative.hpp>
#include<onerut_request/request_print_value.hpp>
#include<onerut_parser_rules/asset_receipt.hpp>

namespace onerut_parser_rules {

    void print_receipt(std::ostream& stream, const onerut_parser_exec::Asset& asset, std::string line_prefix) {
        // ---------------------------------------------------------------------
        if (onerut_parser_exec::utility::is_unset_ref(asset)) {
            stream << line_prefix << "[asset] "
                    << "Asset is an "
                    << esc::manip::italic << "unset reference" << esc::manip::reset << "."
                    << std::endl;
            const auto result_reference = *(asset.reference_or_empty());
            stream << line_prefix << "[asset] "
                    << "reference name = " << string_utils::StreamToGreek(result_reference->get_name())
                    << std::endl;
        } else if (onerut_parser_exec::utility::is_const_ref(asset)) {
            stream << line_prefix << "[asset] "
                    << "Asset is a "
                    << esc::manip::italic << "const reference" << esc::manip::reset << "."
                    << std::endl;
            const auto result_reference = *(asset.reference_or_empty());
            stream << line_prefix << "[asset] "
                    << "reference name = " << string_utils::StreamToGreek(result_reference->get_name())
                    << std::endl;
        } else if (onerut_parser_exec::utility::is_not_const_ref(asset)) {
            stream << line_prefix << "[asset] "
                    << "Asset is a "
                    << esc::manip::italic << "not const reference" << esc::manip::reset << "."
                    << std::endl;
            const auto result_reference = *(asset.reference_or_empty());
            stream << line_prefix << "[asset] "
                    << "reference name = " << string_utils::StreamToGreek(result_reference->get_name())
                    << std::endl;
        } else {
            stream << line_prefix << "[asset] " << "Asset is not a reference." << std::endl;
        }
        // ---------------------------------------------------------------------
        if (asset.deref().is_empty()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-deref is an " << esc::manip::italic << "empty asset" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_request::ImperativeRequest>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is an " << esc::manip::italic << "imperative-request" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_request::PrintValueRequest>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is an " << esc::manip::italic << "print-value-request" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_compile_error()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is an " << esc::manip::italic << "error" << esc::manip::reset << "."
                    << std::endl;
            const auto error = *asset.deref().compile_error_or_empty();
            stream << line_prefix << "[asset-deref] "
                    << "error message = " << error->what() << std::endl;
        } else if (asset.deref().is_given_type<onerut_scalar::Integer>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is an " << esc::manip::italic << "integer-number" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_scalar::Real>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "real-number" << esc::manip::reset << "."
                    << std::endl;
            const auto result_real = *(asset.deref().typed_value_or_empty<onerut_scalar::Real>());
        } else if (asset.deref().is_given_type<onerut_convergence_parameter::ConvergenceParameter>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "convergence-parameter" << esc::manip::reset << "."
                    << std::endl;
            //const auto result_real = *(asset.deref().typed_value_or_empty<onerut_scalar::Real>());
        } else if (asset.deref().is_given_type<onerut_scalar::Complex>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "complex-number" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::CustomDomain>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "custom-type-normal-domain" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::OscillatorDomain>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "oscillator-type-normal-domain" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::SpinDomain>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "spin-type-normal-domain" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::KronDomain>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "kron-type-normal-domain" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::StateIndex>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "normal-domain-state-index" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::KronPlaceholder>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "kron-domain-placeholder" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::AbstractRealOperator>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is a " << esc::manip::italic << "normal-domain-operator" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::Eig>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is " << esc::manip::italic << "normal-domain-eig" << esc::manip::reset << "."
                    << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::Mean>()) {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer is " << esc::manip::italic << "normal-domain-mean" << esc::manip::reset << "."
                    << std::endl;
        } else {
            stream << line_prefix << "[asset-deref] "
                    << "Asset-defer type is not supported by receipt."
                    << std::endl;
        }

    }

}

#endif