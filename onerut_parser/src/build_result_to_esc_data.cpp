#include<onerut_parser/build_result_to_esc_data.hpp>
#include<onerut_scalar/scalar.hpp>

namespace onerut_parser {

    esc::EscData build_result_to_esc_data(const BuildResult&) {
        // TODO
        return esc::EscDataBuilder() << esc::manip::build_esc_data;
    }

}