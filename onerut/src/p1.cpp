#include<iostream>
#include<fstream>
#include<iomanip>
#include<filesystem>

#include<esc/esc_manip.hpp>
#include<onerut_parser/string_span.hpp>
#include<onerut_parser/unicode_support.hpp>
#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_source.hpp>
#include<onerut_parser/ast_compile_result.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_parser/function_global.hpp>
#include<onerut_scalar/scalar.hpp>


#include<optional>

bool
execute_line(std::shared_ptr<std::u32string> uline) {
    // #########################################################################
    std::cout << esc::manip::bg_yellow << "Processsing "
            << esc::manip::blue << unicode_to_utf8(*uline) << esc::manip::color_default
            << "...";
    std::cout << std::endl;
    // #########################################################################
    const auto parsed_x3_info = onerut_parser::parse(uline);
    // -------------------------------------------------------------------------
    //std::cout << "onerut_ast::x3:" << std::endl;
    //    print(parsed_x3_info);
    if (!parsed_x3_info.succes()) {
        //std::cout << "Fail to parse line: " << esc::manip::red << unicode_to_utf8(*uline) << esc::manip::reset << "." << std::endl;
        //std::cout << "match: " << parsed_x3_info.match << ", hit_end: " << parsed_x3_info.hit_end() << "." << std::endl;
        const auto parsed_view = onerut_parser::to_u32string_view(parsed_x3_info.parsed_span());
        const auto not_parsed_view = onerut_parser::to_u32string_view(parsed_x3_info.not_parsed_span());
        std::cout << esc::manip::bg_green << unicode_to_utf8(parsed_view)
                << esc::manip::bg_red << unicode_to_utf8(not_parsed_view);
        std::cout << std::endl;
        return false;
    }

    // #########################################################################
    const auto ast_source_head = onerut_parser::onerut_ast::to_ast_source(
            parsed_x3_info.ast_head,
            parsed_x3_info.input,
            parsed_x3_info.positions);
    // -------------------------------------------------------------------------
    //    const auto ast_source_chart = ast_source_head->to_chart();
    //    std::cout << "onerut_ast::source:" << std::endl;
    //    onerut_parser::print_chart(parsed_x3_info.input, ast_source_chart);
    // #########################################################################
    const auto ast_compile_result_head = ast_source_head->compile();
    // -------------------------------------------------------------------------
    const auto ast_compile_result_chart = ast_compile_result_head->to_chart();
    //std::cout << "onerut_ast::compile_result:" << std::endl;
    onerut_parser::print_chart(parsed_x3_info.input, ast_compile_result_chart);
    // -------------------------------------------------------------------------
    onerut_parser::CompileResult compile_result = ast_compile_result_head->compile_result;
    if (compile_result.dereference().is_compile_error()) {
        std::cout << "Result is an error." << std::endl;
        std::cout << "Message = " << (*compile_result.dereference().compile_error_or_empty())->what() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Long>()) {
        std::cout << "Result is an integer." << std::endl;
        std::shared_ptr<onerut_scalar::Long> result_long = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Long>());
        std::cout << "Value = " << result_long->value_long() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Double>()) {
        std::cout << "Result is a double." << std::endl;
        std::shared_ptr<onerut_scalar::Double> result_double = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Double>());
        std::cout << "Value = " << std::setprecision(20) << result_double->value_double() << std::endl;
    } else {
        std::cout << "Result is not an integer, nor a double, nor an error." << std::endl;
    }
    std::cout << std::endl;
    return true;
}

bool
execute_script_ulines(const std::vector<std::shared_ptr<std::u32string>>&ulines) {
    return std::all_of(cbegin(ulines), cend(ulines),
            [](const std::shared_ptr<std::u32string> &line) {
                return execute_line(line);
            });
}

std::vector<std::shared_ptr<std::u32string>>
load_script_ulines_from_file(const std::filesystem::path& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Problem z otwarciem pliku" << std::endl;
    }
    std::vector<std::shared_ptr < std::u32string >> ulines;
    std::string line;
    while (std::getline(file, line)) {
        std::cout << "load line: " << line << std::endl;
        auto uline = std::make_shared<std::u32string>(unicode_from_utf8(line));
        ulines.push_back(uline);
    }
    return ulines;
}

bool execute_script_file(const std::filesystem::path& file_path) {
    auto ulines = load_script_ulines_from_file(file_path);
    onerut_parser::GlobalIdentifiers::instance().put_e();
    onerut_parser::GlobalIdentifiers::instance().put_pi();
    onerut_parser::GlobalFunctions::instance().put_cmath();
    return execute_script_ulines(ulines);
}

void temp_testing() {

    //    std::cout << sizeof(int) << std::endl;
    //    std::cout << sizeof(std::optional<int>) << std::endl;
    //    std::cout << sizeof(std::pair<int,bool>) << std::endl;
    //    std::cout << sizeof(std::pair<bool,int>) << std::endl;
    
    onerut_parser::GlobalIdentifiers::instance().put_e();
    onerut_parser::GlobalIdentifiers::instance().put_pi();
    onerut_parser::GlobalFunctions::instance().put_cmath();

    //std::string input = "  _alg(_67j, foo(  7  , 8 ) , (xx2s) ) kota* 56.8 ";
    //std::string input  = "  $ ";
    //const std::string input = "  3.0^6@t+_alg((5->4-7/foo(6)), 8.9*ola::ala,-pi+9,-7+9)*(-(9))+(-(9.0)+1) ";
    //std::string input = "(9/2+3)*7.0";
    //std::cout << (9 / 2 + 3)*7.0 << std::endl;
    //long i = 10000000000000000l;
    //std::cout << i + 1 << std::endl;
    //std::cout << std::setprecision(20) << 10000000000000000 + 1. << std::endl;
    //return 1;
    //std::string input = " (13/2*0.5+ (-(7.8*(5+5*7)) + 8. + -.8) /9) ";
    //std::cout << (13 / 2 * 0.5 + (-(7.8 * (5 + 5 * 7)) + 8. + -.8) / 9) << std::endl;
    //std::string input = "10000000 + 1.";
    //std::string input = "1000000000000000000000+1.";
    //const std::string input = "  10+pi/2 ";
    //const std::string input = "new x := 10 ";

    std::vector<std::shared_ptr < std::u32string>> lines;
    //    lines.push_back(std::make_shared < std::u32string>(U"(2+4*3)+pi/2"));
    lines.push_back(std::make_shared < std::u32string>(U"x:=(2+4*3)+pi/2"));
    lines.push_back(std::make_shared < std::u32string>(U"x+7"));
    lines.push_back(std::make_shared < std::u32string>(U"x:=40"));
    lines.push_back(std::make_shared < std::u32string>(U"x+4"));
    lines.push_back(std::make_shared < std::u32string>(U"sqrt(4.0)"));
    lines.push_back(std::make_shared < std::u32string>(U"max(3,2)"));
    lines.push_back(std::make_shared < std::u32string>(U"sin(pi/4)/sqrt(2)"));
    lines.push_back(std::make_shared < std::u32string>(U"3^2"));
    execute_script_ulines(lines);

}

int main(int argc, char** argv) {
    if (argc == 2) {
        std::cout << "enter script mode" << std::endl;
        const std::filesystem::path file_path(argv[1]);
        std::cout << "file path: " << file_path << std::endl;
        execute_script_file(file_path);
    } else {
        temp_testing();
    }
}