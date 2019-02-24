#include<iostream>
#include<fstream>
#include<iomanip>
#include<optional>
#include<filesystem>

#include<esc/esc_manip.hpp>
#include<string_utils/greek_support.hpp>

#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_source.hpp>
#include<onerut_parser/ast_asset.hpp>
#include<onerut_parser/function_factory_container.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/asset_utility.hpp>
#include<onerut_parser/asset_receipt.hpp>

//--------------------------------------------

bool
execute_line(std::shared_ptr<const std::string> line) {
    // *************************************************************************
    std::cout << esc::manip::bg_yellow << "Processsing "
            << esc::manip::blue << string_utils::StreamToGreek(*line) << esc::manip::color_default
            << "...";
    std::cout << std::endl;
    // *************************************************************************
    // *************  The Parser stage    **************************************
    // *************************************************************************    
    const auto parsed_x3_info = onerut_parser::parse(line);
    // -------------------------------------------------------------------------
    //    print(parsed_x3_info);
    if (!parsed_x3_info.succes()) {
        if (!parsed_x3_info.match) {
            std::cout << "Fail to parse line: " << std::endl;
            std::cout << esc::manip::red << string_utils::StreamToGreek(*line) << esc::manip::reset << "." << std::endl;
        } else {
            const auto parsed_view = onerut_parser::to_string_view(parsed_x3_info.parsed_span());
            const auto not_parsed_view = onerut_parser::to_string_view(parsed_x3_info.not_parsed_span());
            std::cout << esc::manip::bg_green << string_utils::StreamToGreek(parsed_view)
                    << esc::manip::bg_red << string_utils::StreamToGreek(not_parsed_view);
            std::cout << std::endl;
        }
        return false;
    }
    // *************************************************************************
    // *************  The source creation stage:     ***************************
    // *************************************************************************    
    const auto ast_source_head = onerut_parser::onerut_ast::to_ast_source(
            parsed_x3_info.ast_head,
            parsed_x3_info.input,
            parsed_x3_info.positions);
    // -------------------------------------------------------------------------
    // const auto ast_source_ast_chart = ast_source_head->to_ast_chart();
    // onerut_parser::print_ast_chart(parsed_x3_info.input, ast_source_ast_chart, , "[source ] ");
    // *************************************************************************
    // *************  Compilation stage:     ***********************************
    // *************************************************************************
    const auto ast_asset_head = ast_source_head->compile();
    // -------------------------------------------------------------------------
    const auto asset_ast_chart = ast_asset_head->to_ast_chart();
    onerut_parser::print_ast_chart(std::cout, parsed_x3_info.input, asset_ast_chart, "[diagram] ");
    const auto asset_errors_chart = ast_asset_head->to_errors_chart();
    onerut_parser::print_errors_chart(std::cout, parsed_x3_info.input, asset_errors_chart, "[errors ] ");
    const auto& asset = ast_asset_head->asset;
    onerut_parser::print_receipt(std::cout, asset, "[receipt] ");
    // *************************************************************************
    std::cout << std::endl;
    return true;// TODO
}

std::vector<std::shared_ptr<const std::string>>
load_script_lines_from_file(const std::filesystem::path& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Input file opening error." << std::endl;
        exit(1);
    }
    std::vector<std::shared_ptr <const std::string >> lines;
    std::string line;
    while (std::getline(file, line)) {
        std::cout << "load line: " << line << std::endl;
        auto line_ptr = std::make_shared<const std::string>(line);
        lines.push_back(line_ptr);
    }
    return lines;
}

bool
execute_script_lines(const std::vector<std::shared_ptr<const std::string>>&lines) {
    return std::all_of(cbegin(lines), cend(lines),
            [](const std::shared_ptr<const std::string> &line) {
                return execute_line(line);
            });
}

bool execute_script_file(const std::filesystem::path& file_path) {
    auto lines = load_script_lines_from_file(file_path);
    onerut_parser::FunctionFactoryContainer::global_instance().put_cmath();
    onerut_parser::FunctionFactoryContainer::global_instance().put_onerut_functions();
    return execute_script_lines(lines);
}

void temp_testing() {
    std::vector<std::shared_ptr<const std::string> > lines;
    lines.push_back(std::make_shared<const std::string>("x:=(2+4*3)+pi/2"));
    lines.push_back(std::make_shared<const std::string>("x+7"));
    lines.push_back(std::make_shared<const std::string>("x:=40"));
    lines.push_back(std::make_shared<const std::string>("x+4"));
    lines.push_back(std::make_shared<const std::string>("sqrt(4.0)"));
    lines.push_back(std::make_shared<const std::string>("max(3,2)"));
    lines.push_back(std::make_shared<const std::string>("sin(pi/4)/sqrt(2)"));
    lines.push_back(std::make_shared<const std::string>("3^2"));
    lines.push_back(std::make_shared<const std::string>("5i"));
    lines.push_back(std::make_shared<const std::string>("5i+6 + 7i"));
    lines.push_back(std::make_shared<const std::string>("conj(3i+5i*7.i)"));
    lines.push_back(std::make_shared<const std::string>("pow(2i,2)"));
    lines.push_back(std::make_shared<const std::string>("cx_pow(2i,2)"));
    lines.push_back(std::make_shared<const std::string>("pow(2,2)"));
    lines.push_back(std::make_shared<const std::string>("pow(2,2.0)"));
    lines.push_back(std::make_shared<const std::string>("pow(2,2.2)"));
    lines.push_back(std::make_shared<const std::string>("sqrt(2)"));
    lines.push_back(std::make_shared<const std::string>("sqrt(2.0)"));
    lines.push_back(std::make_shared<const std::string>("sqrt(sqrt(2)*1i)"));
    lines.push_back(std::make_shared<const std::string>("norm(sqrt(sqrt(2)*1i))"));
    lines.push_back(std::make_shared<const std::string>("re_sqrt(2)"));
    lines.push_back(std::make_shared<const std::string>("cx_sqrt(2)"));
    lines.push_back(std::make_shared<const std::string>("new z := sqrt(2i)"));
    lines.push_back(std::make_shared<const std::string>("re := real(z)"));
    lines.push_back(std::make_shared<const std::string>("im := imag(z)"));
    lines.push_back(std::make_shared<const std::string>("xx := re+im+ pi + kupi + (2*7+7)+ alpha*9 + piwo*(3*8+Ups+ups+Up+up) + pi"));
    lines.push_back(std::make_shared<const std::string>("xx := e^[1i*pi]"));
    lines.push_back(std::make_shared<const std::string>("xx := re_sqrt(2)"));
    lines.push_back(std::make_shared<const std::string>("re_sqrt(2)"));
    lines.push_back(std::make_shared<const std::string>("cx_sqrt(2)"));
    lines.push_back(std::make_shared<const std::string>("real(3i+5i*7.i)"));
    lines.push_back(std::make_shared<const std::string>("imag(3i+5i*7.i)"));
    lines.push_back(std::make_shared<const std::string>("conj(3i+5i*7.i)"));
    lines.push_back(std::make_shared<const std::string>("abs(-7)"));
    lines.push_back(std::make_shared<const std::string>("abs(1i+1)"));
    lines.push_back(std::make_shared<const std::string>("op_to_mat(1i+1)"));
    lines.push_back(std::make_shared<const std::string>("ELECTRON_DOMAIN := create_normal_domain(AC, CA, EG, GE)"));
    lines.push_back(std::make_shared<const std::string>("ELECTRON_DOMAIN"));
    lines.push_back(std::make_shared<const std::string>("op1 := normalop_hop(5, AC, CA)"));
    lines.push_back(std::make_shared<const std::string>("op2 := normalop_hop(3, CA, EG)"));
    lines.push_back(std::make_shared<const std::string>("op1 * op2"));
    lines.push_back(std::make_shared<const std::string>("op2 * op1"));
    
    //lines.push_back(std::make_shared<const std::string>("EG"));
    //lines.push_back(std::make_shared<const std::string>("create_normal_domain(AC2_alpha_bcdefgh, CA2, EG2_gamma_2, GE2)"));
    //lines.push_back(std::make_shared<const std::string>("EG2"));
    //lines.push_back(std::make_shared<const std::string>("h := normalop_hop(5, AC2_alpha_bcdefgh, CA2)"));
    //lines.push_back(std::make_shared<const std::string>("d := normalop_diag(70000000000000.8, GE2)"));
    //    lines.push_back(std::make_shared<const std::string>("normalop_diag(7.8, EG2)"));
    //    lines.push_back(std::make_shared<const std::string>("normalop_print(h)"));
    //    lines.push_back(std::make_shared<const std::string>("normalop_print(d)"));
    //    lines.push_back(std::make_shared<const std::string>("z := normalop_zero(ELECTRON_DOMAIN)"));
    //    lines.push_back(std::make_shared<const std::string>("normalop_print(z)"));
    //    lines.push_back(std::make_shared<const std::string>("zdh := z + d + h"));
    //    lines.push_back(std::make_shared<const std::string>("normalop_print(zdh)"));
    //    lines.push_back(std::make_shared<const std::string>("zdh2 := 5 * zdh"));
    //    lines.push_back(std::make_shared<const std::string>("zdh3 := zdh * 5.0"));
    //    lines.push_back(std::make_shared<const std::string>("zdh4 := zdh * zdh"));
    //    lines.push_back(std::make_shared<const std::string>("normalop_print(zdh2)"));
    //    lines.push_back(std::make_shared<const std::string>("normalop_diag(7.8, EG2) + normalop_diag(7.8, AC)"));
    //    lines.push_back(std::make_shared<const std::string>("normalop_hop(5, EG2, CA)"));
    //    lines.push_back(std::make_shared<const std::string>("yyy := 6 + 8 * (4 + hh(7+8) + t + omega(rho_1(chi_7))) + pi"));    

    onerut_parser::FunctionFactoryContainer::global_instance().put_cmath();
    onerut_parser::FunctionFactoryContainer::global_instance().put_onerut_functions();

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