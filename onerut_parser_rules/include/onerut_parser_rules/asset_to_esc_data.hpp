#ifndef ONERUT_PARSER_BUILD_RESULT_TO_ESC_DATA
#define ONERUT_PARSER_BUILD_RESULT_TO_ESC_DATA

#include<esc/esc_manip.hpp>
#include<onerut_parser_exec/asset.hpp>

namespace onerut_parser_rules {

    esc::EscData asset_to_esc_data(const onerut_parser_exec::Asset&);

}
#endif
