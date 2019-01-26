#ifndef ONERUT_PARSER_BUILD_RESULT_TO_ESC_DATA
#define ONERUT_PARSER_BUILD_RESULT_TO_ESC_DATA

#include<onerut_parser/build_result.hpp>
#include<esc/esc_manip.hpp>

namespace onerut_parser {

    esc::EscData build_result_to_esc_data(const BuildResult&);

}
#endif
