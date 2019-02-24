#ifndef ONERUT_PARSER_ASSET_RECEIPT
#define ONERUT_PARSER_ASSET_RECEIPT

#include<esc/esc_manip.hpp>
#include<string_utils/greek_support.hpp>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/to_string.hpp>

#include<onerut_parser/asset.hpp>
#include<onerut_parser/asset_utility.hpp>

#include<onerut_parser/asset_receipt.hpp>

#include "string_utils/greek_support.hpp"

namespace onerut_parser {

    void print_receipt(std::ostream& stream, const Asset& asset, std::string line_prefix) {
        // ---------------------------------------------------------------------
        if (onerut_parser::utility::is_unset_ref(asset)) {
            stream << line_prefix << "[ref] " << "Asset is an " << esc::manip::italic << "unset reference" << esc::manip::reset << "." << std::endl;
            const auto result_reference = *(asset.reference_or_empty());
            stream << line_prefix << "[ref] " << "Reference name = " << string_utils::StreamToGreek(result_reference->get_name()) << std::endl;
        } else if (onerut_parser::utility::is_const_ref(asset)) {
            stream << line_prefix << "[ref] " << "Asset is a " << esc::manip::italic << "const reference" << esc::manip::reset << "." << std::endl;
            const auto result_reference = *(asset.reference_or_empty());
            stream << line_prefix << "[ref] " << "Reference name = " << string_utils::StreamToGreek(result_reference->get_name()) << std::endl;
        } else if (onerut_parser::utility::is_not_const_ref(asset)) {
            stream << line_prefix << "[ref] " << "Asset is a " << esc::manip::italic << "not const reference" << esc::manip::reset << "." << std::endl;
            const auto result_reference = *(asset.reference_or_empty());
            stream << line_prefix << "[ref] " << "Reference name = " << string_utils::StreamToGreek(result_reference->get_name()) << std::endl;
        } else {
            stream << line_prefix << "[ref] " << "Asset is not a reference." << std::endl;            
        }
        // ---------------------------------------------------------------------
        if (asset.deref().is_empty()) {
            stream << line_prefix << "[deref] " << "Asset-deref is an " << esc::manip::italic << "empty asset." << std::endl;
        } else if (asset.deref().is_compile_error()) {
            stream << line_prefix << "[deref] " << "Asset-defer is an " << esc::manip::italic << "error." << std::endl;
            const auto error = *asset.deref().compile_error_or_empty();
            stream << line_prefix << "[deref] " << "Error message = " << error->what() << std::endl;
        } else if (asset.deref().is_given_type<onerut_scalar::Integer>()) {
            stream << line_prefix << "[deref] " << "Asset-defer is an " << esc::manip::italic << "integer-number." << std::endl;
            const auto result_integer = *(asset.deref().typed_value_or_empty<onerut_scalar::Integer>());
            stream << line_prefix << "[deref] " << "Value = " << result_integer->value_integer() << std::endl;
        } else if (asset.deref().is_given_type<onerut_scalar::Real>()) {
            stream << line_prefix << "[deref] " << "Asset-defer is a " << esc::manip::italic << "real-number." << std::endl;
            const auto result_real = *(asset.deref().typed_value_or_empty<onerut_scalar::Real>());
            stream << line_prefix << "[deref] " << "Value = " << result_real->value_real() << std::endl;
        } else if (asset.deref().is_given_type<onerut_scalar::Complex>()) {
            stream << line_prefix << "[deref] " << "Asset-defer is a " << esc::manip::italic << "complex-number." << std::endl;
            const auto result_complex = *(asset.deref().typed_value_or_empty<onerut_scalar::Complex>());
            stream << line_prefix << "[deref] " << "Value = " << result_complex->value_complex() << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::StateIndex>()) {
            stream << line_prefix << "[deref] " << "Asset-defer is a " << esc::manip::italic << "normal-domain-state-index ." << std::endl;
            const auto state = *(asset.deref().typed_value_or_empty<onerut_normal_operator::StateIndex>());
            stream << line_prefix << "[deref] " << "Value = " << state->to_str() << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::Domain>()) {
            stream << line_prefix << "[deref] " << "Asset-defer is a " << esc::manip::italic << "normal-domain." << std::endl;
            const auto domain = *(asset.deref().typed_value_or_empty<onerut_normal_operator::Domain>());
            stream << line_prefix << "[deref] " << "Value = " << onerut_normal_operator::to_string(*domain) << std::endl;
        } else if (asset.deref().is_given_type<onerut_normal_operator::AbstractOperator>()) {
            stream << line_prefix << "[deref] " << "Asset-defer is a " << esc::manip::italic << "normal-domain-operator" << esc::manip::reset << "." << std::endl;
            const auto op = *(asset.deref().typed_value_or_empty<onerut_normal_operator::AbstractOperator>());
            //stream << line_prefix << "Operator domain = " << onerut_normal_operator::to_string(*op->get_domain()) << std::endl;
            stream << onerut_normal_operator::to_string(*op, line_prefix + "[deref] ");
        } else {
            stream << line_prefix << "[deref] " << "Asset-defer type is not supported by receipt." << std::endl;
        }
        // ---------------------------------------------------------------------
    }

}

#endif