#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

#include<onerut_parser/asset_utility.hpp>
#include<onerut_parser/asset_to_esc_data.hpp>

namespace onerut_parser {

    esc::EscData asset_to_esc_data(const Asset& asset) {
        if (utility::is_unset_ref(asset))
            return esc::EscDataBuilder() << esc::manip::bg_blue << esc::manip::build_esc_data;
        if (asset.deref().is_empty())
            return esc::EscDataBuilder() << esc::manip::bg_magenta << esc::manip::build_esc_data;
        if (asset.deref().is_compile_error()) {
            if (std::dynamic_pointer_cast<CompileArgumentsError>(*asset.deref().compile_error_or_empty()))
                return esc::EscDataBuilder() << esc::manip::bg_yellow << esc::manip::build_esc_data;
            if (std::dynamic_pointer_cast<CompilerNotImplementedError>(*asset.deref().compile_error_or_empty()))
                return esc::EscDataBuilder() << esc::manip::bg_magenta << esc::manip::build_esc_data;
            return esc::EscDataBuilder() << esc::manip::bg_red << esc::manip::build_esc_data;
        }
        if (asset.deref().is_given_type<onerut_scalar::Integer>())
            return esc::EscDataBuilder() << esc::manip::blue << esc::manip::build_esc_data;
        if (asset.deref().is_given_type<onerut_scalar::Real>())
            return esc::EscDataBuilder() << esc::manip::cyan << esc::manip::build_esc_data;
        if (asset.deref().is_given_type<onerut_scalar::Complex>())
            return esc::EscDataBuilder() << esc::manip::green << esc::manip::build_esc_data;
        if (asset.deref().is_given_type<onerut_normal_operator::Domain>())
            return esc::EscDataBuilder() << esc::manip::italic << esc::manip::yellow << esc::manip::build_esc_data;
        if (asset.deref().is_given_type<onerut_normal_operator::StateIndex>())
            return esc::EscDataBuilder() << esc::manip::italic << esc::manip::yellow << esc::manip::build_esc_data;
        if (asset.deref().is_given_type<onerut_normal_operator::AbstractOperator>())
            return esc::EscDataBuilder() << esc::manip::bold << esc::manip::yellow << esc::manip::build_esc_data;

        return esc::EscDataBuilder() << esc::manip::build_esc_data;
    }

}