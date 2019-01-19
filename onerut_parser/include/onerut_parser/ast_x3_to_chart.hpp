#ifndef ONERUT_PARSER_AST_X3_TO_CHART
#define ONERUT_PARSER_AST_X3_TO_CHART

#include<onerut_parser/ast_x3.hpp>

namespace onerut_parser::onerut_ast::x3 {

    extern const char32_t chart_fill_character_1;
    extern const char32_t chart_fill_character_2;
    extern const char32_t chart_fill_character_3;
    std::vector<std::u32string> to_u32string_chart(
            const ExpressionInfo& info,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);

}

#endif