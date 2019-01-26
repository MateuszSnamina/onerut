#include<onerut_parser/build_result_to_esc_data.hpp>
#include<onerut_scalar/scalar.hpp>

namespace onerut_parser {

    esc::EscData build_result_to_esc_data(const BuildResult& build_result) {
        if (build_result.is_empty())
            return esc::EscDataBuilder() << esc::manip::bg_magenta << esc::manip::build_esc_data;
        if (build_result.is_error())
            return esc::EscDataBuilder() << esc::manip::bg_red << esc::manip::build_esc_data;
        if (build_result.is_given_type<onerut_scalar::Int>())
            return esc::EscDataBuilder() << esc::manip::blue << esc::manip::build_esc_data;
        if (build_result.is_given_type<onerut_scalar::Double>())
            return esc::EscDataBuilder() << esc::manip::cyan << esc::manip::build_esc_data;
        return esc::EscDataBuilder() << esc::manip::build_esc_data;
    }

}