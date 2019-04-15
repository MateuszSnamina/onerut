#ifndef ONERUT_PARSER_BUILD_RESULT_TO_ESC_DATA
#define ONERUT_PARSER_BUILD_RESULT_TO_ESC_DATA

#include<onerut_parser/asset.hpp>
#include<esc/esc_manip.hpp>

namespace onerut_parser {

    esc::EscData asset_to_esc_data(const Asset&);

}
#endif
