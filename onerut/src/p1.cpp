#include<iostream>
#include<fstream>
#include<iomanip>
#include<optional>
#include<filesystem>

#include<esc/esc_manip.hpp>
#include<string_utils/string_span.hpp>
#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_source.hpp>
#include<onerut_parser/ast_compile_result.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_parser/function_global.hpp>
#include<onerut_scalar/scalar_abstract.hpp>

#include<onerut_operator/operator.hpp>

bool
execute_line(std::shared_ptr<std::string> line) {
    // #########################################################################
    std::cout << esc::manip::bg_yellow << "Processsing "
            << esc::manip::blue << *line << esc::manip::color_default
            << "...";
    std::cout << std::endl;
    // #########################################################################
    const auto parsed_x3_info = onerut_parser::parse(line);
    // -------------------------------------------------------------------------
    //std::cout << "onerut_ast::x3:" << std::endl;
    //    print(parsed_x3_info);
    if (!parsed_x3_info.succes()) {
        //std::cout << "Fail to parse line: " << esc::manip::red << unicode_to_utf8(*line) << esc::manip::reset << "." << std::endl;
        //std::cout << "match: " << parsed_x3_info.match << ", hit_end: " << parsed_x3_info.hit_end() << "." << std::endl;
        const auto parsed_view = onerut_parser::to_string_view(parsed_x3_info.parsed_span());
        const auto not_parsed_view = onerut_parser::to_string_view(parsed_x3_info.not_parsed_span());
        std::cout << esc::manip::bg_green << parsed_view
                << esc::manip::bg_red << not_parsed_view;
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
        std::cout << "[receipt] expression is an error." << std::endl;
        const auto error = *compile_result.dereference().compile_error_or_empty();
        std::cout << error->what() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Integer>()) {
        std::cout << "[receipt] expression is an integer number." << std::endl;
        const auto result_integer = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Integer>());
        std::cout << "[receipt] onerut_value = " << result_integer->value_integer() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Real>()) {
        std::cout << "[receipt] expression is a real number." << std::endl;
        const auto result_real = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Real>());
        std::cout << "[receipt] onerut_value = " << result_real->value_real() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Complex>()) {
        std::cout << "[receipt] expression is a complex number." << std::endl;
        const auto result_complex = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Complex>());
        std::cout << "[receipt] onerut_value = " << result_complex->value_complex() << std::endl;
    } else {
        std::cout << "[receipt] result is not an error nor a scalar." << std::endl;
    }
    std::cout << std::endl;
    return true;
}

bool
execute_script_lines(const std::vector<std::shared_ptr<std::string>>&lines) {
    return std::all_of(cbegin(lines), cend(lines),
            [](const std::shared_ptr<std::string> &line) {
                return execute_line(line);
            });
}

std::vector<std::shared_ptr<std::string>>
load_script_lines_from_file(const std::filesystem::path& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Problem z otwarciem pliku" << std::endl;
    }
    std::vector<std::shared_ptr < std::string >> lines;
    std::string line;
    while (std::getline(file, line)) {
        std::cout << "load line: " << line << std::endl;
        auto line_ptr = std::make_shared<std::string>(line);
        lines.push_back(line_ptr);
    }
    return lines;
}

bool execute_script_file(const std::filesystem::path& file_path) {
    auto lines = load_script_lines_from_file(file_path);
    onerut_parser::GlobalIdentifiers::instance().put_e();
    onerut_parser::GlobalIdentifiers::instance().put_pi();
    onerut_parser::GlobalFunctions::instance().put_cmath();
    return execute_script_lines(lines);
}

void temp_testing() {

    std::vector<std::shared_ptr < std::string>> lines;
    lines.push_back(std::make_shared < std::string>("x:=(2+4*3)+pi/2"));
    lines.push_back(std::make_shared < std::string>("x+7"));
    lines.push_back(std::make_shared < std::string>("x:=40"));
    lines.push_back(std::make_shared < std::string>("x+4"));
    lines.push_back(std::make_shared < std::string>("sqrt(4.0)"));
    lines.push_back(std::make_shared < std::string>("max(3,2)"));
    lines.push_back(std::make_shared < std::string>("sin(pi/4)/sqrt(2)"));
    lines.push_back(std::make_shared < std::string>("3^2"));
    lines.push_back(std::make_shared < std::string>("5i"));
    lines.push_back(std::make_shared < std::string>("5i+6 + 7i"));
    onerut_parser::GlobalIdentifiers::instance().put_e();
    onerut_parser::GlobalIdentifiers::instance().put_pi();
    onerut_parser::GlobalFunctions::instance().put_cmath();
    execute_script_lines(lines);

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