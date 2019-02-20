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
#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/function_factory_global.hpp>
#include<onerut_parser/asset_utility.hpp>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>

#include<type_traits>


//--------------------------------------------

bool
execute_line(std::shared_ptr<std::string> line) {
    // #########################################################################
    std::cout << esc::manip::bg_yellow << "Processsing "
            << esc::manip::blue << string_utils::to_greek(*line) << esc::manip::color_default
            << "...";
    std::cout << std::endl;
    // #########################################################################
    const auto parsed_x3_info = onerut_parser::parse(line);
    // -------------------------------------------------------------------------
    //std::cout << "onerut_ast::x3:" << std::endl;
    //    print(parsed_x3_info);
    if (!parsed_x3_info.succes()) {
        if (!parsed_x3_info.match) {
            std::cout << "Fail to parse line: " << std::endl;
            std::cout << esc::manip::red << *line << esc::manip::reset << "." << std::endl;
        } else {
            const auto parsed_view = onerut_parser::to_string_view(parsed_x3_info.parsed_span());
            const auto not_parsed_view = onerut_parser::to_string_view(parsed_x3_info.not_parsed_span());
            std::cout << esc::manip::bg_green << parsed_view
                    << esc::manip::bg_red << not_parsed_view;
            std::cout << std::endl;
        }
        return false;
    }
    // #########################################################################
    const auto ast_source_head = onerut_parser::onerut_ast::to_ast_source(
            parsed_x3_info.ast_head,
            parsed_x3_info.input,
            parsed_x3_info.positions);
    // -------------------------------------------------------------------------
    //    const auto ast_source_chart = ast_source_head->to_chart();
    //    onerut_parser::print_chart(parsed_x3_info.input, ast_source_chart, , "[source ] ");
    // #########################################################################
    const auto ast_asset_head = ast_source_head->compile();
    // -------------------------------------------------------------------------
    const auto ast_asset_chart = ast_asset_head->to_chart();
    onerut_parser::print_chart(parsed_x3_info.input, ast_asset_chart, "[diagram] ");
    // -------------------------------------------------------------------------
    onerut_parser::Asset asset = ast_asset_head->asset;

    if (asset.deref().is_compile_error()) {
        std::cout << "[receipt] Expression is an error." << std::endl;
        const auto error = *asset.deref().compile_error_or_empty();
        std::cout << "[receipt] Error message = " << error->what() << std::endl;
    } else if (asset.deref().is_given_type<onerut_scalar::Integer>()) {
        std::cout << "[receipt] Expression is an integer-number." << std::endl;
        const auto result_integer = *(asset.deref().typed_value_or_empty<onerut_scalar::Integer>());
        std::cout << "[receipt] Value = " << result_integer->value_integer() << std::endl;
    } else if (asset.deref().is_given_type<onerut_scalar::Real>()) {
        std::cout << "[receipt] Expression is a real-number." << std::endl;
        const auto result_real = *(asset.deref().typed_value_or_empty<onerut_scalar::Real>());
        std::cout << "[receipt] Value = " << result_real->value_real() << std::endl;
    } else if (asset.deref().is_given_type<onerut_scalar::Complex>()) {
        std::cout << "[receipt] Expression is a complex-number." << std::endl;
        const auto result_complex = *(asset.deref().typed_value_or_empty<onerut_scalar::Complex>());
        std::cout << "[receipt] Value = " << result_complex->value_complex() << std::endl;
    } else if (asset.deref().is_given_type<onerut_normal_operator::StateIndex>()) {
        std::cout << "[receipt] Expression is a normal-domain-state-index ." << std::endl;
        const auto state = *(asset.deref().typed_value_or_empty<onerut_normal_operator::StateIndex>());
        std::cout << "[receipt] Value = " << state->to_str() << std::endl;
    } else if (asset.deref().is_given_type<onerut_normal_operator::Domain>()) {
        std::cout << "[receipt] Expression is a normal-domain." << std::endl;
        const auto domain = *(asset.deref().typed_value_or_empty<onerut_normal_operator::Domain>());
        std::cout << "[receipt] Value = " << domain->to_str() << std::endl;
    } else if (asset.deref().is_given_type<onerut_normal_operator::AbstractOperator>()) {
        std::cout << "[receipt] Expression is a normal-domain-operator." << std::endl;
        const auto op = *(asset.deref().typed_value_or_empty<onerut_normal_operator::AbstractOperator>());
        std::cout << "[receipt] Operator domain = " << op->get_domain()->to_str() << std::endl;
        //std::cout << "[receipt] Operator matrix = " << std::endl;
        //std::cout << op->get_domain()->to_str() << std::endl;
    } else {
        std::cout << "[receipt] Result is not an error nor a scalar." << std::endl;
    }
    std::cout << std::endl;
    return true;
}

std::vector<std::shared_ptr<std::string>>
load_script_lines_from_file(const std::filesystem::path& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Input file opening error." << std::endl;
        exit(1);
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

bool
execute_script_lines(const std::vector<std::shared_ptr<std::string>>&lines) {
    return std::all_of(cbegin(lines), cend(lines),
            [](const std::shared_ptr<std::string> &line) {
                return execute_line(line);
            });
}

bool execute_script_file(const std::filesystem::path& file_path) {
    auto lines = load_script_lines_from_file(file_path);
    onerut_parser::GlobalFunctionFactories::instance().put_cmath();
    onerut_parser::GlobalFunctionFactories::instance().put_onerut_functions();
    return execute_script_lines(lines);
}

void temp_testing() {
    std::vector<std::shared_ptr<std::string> > lines;
    lines.push_back(std::make_shared<std::string>("x:=(2+4*3)+pi/2"));
    lines.push_back(std::make_shared<std::string>("x+7"));
    lines.push_back(std::make_shared<std::string>("x:=40"));
    lines.push_back(std::make_shared<std::string>("x+4"));
    lines.push_back(std::make_shared<std::string>("sqrt(4.0)"));
    lines.push_back(std::make_shared<std::string>("max(3,2)"));
    lines.push_back(std::make_shared<std::string>("sin(pi/4)/sqrt(2)"));
    lines.push_back(std::make_shared<std::string>("3^2"));
    lines.push_back(std::make_shared<std::string>("5i"));
    lines.push_back(std::make_shared<std::string>("5i+6 + 7i"));
    lines.push_back(std::make_shared<std::string>("conj(3i+5i*7.i)"));
    lines.push_back(std::make_shared<std::string>("pow(2i,2)"));
    lines.push_back(std::make_shared<std::string>("cx_pow(2i,2)"));
    lines.push_back(std::make_shared<std::string>("pow(2,2)"));
    lines.push_back(std::make_shared<std::string>("pow(2,2.0)"));
    lines.push_back(std::make_shared<std::string>("pow(2,2.2)"));
    lines.push_back(std::make_shared<std::string>("sqrt(2)"));
    lines.push_back(std::make_shared<std::string>("sqrt(2.0)"));
    lines.push_back(std::make_shared<std::string>("sqrt(sqrt(2)*1i)"));
    lines.push_back(std::make_shared<std::string>("norm(sqrt(sqrt(2)*1i))"));
    lines.push_back(std::make_shared<std::string>("re_sqrt(2)"));
    lines.push_back(std::make_shared<std::string>("cx_sqrt(2)"));
    lines.push_back(std::make_shared<std::string>("new z := sqrt(2i)"));
    lines.push_back(std::make_shared<std::string>("re := real(z)"));
    lines.push_back(std::make_shared<std::string>("im := imag(z)"));
    lines.push_back(std::make_shared<std::string>("xx := re+im+ pi + kupi + (2*7+7)+ alpha*9 + piwo*(3*8+Ups+ups+Up+up) + pi"));
    lines.push_back(std::make_shared<std::string>("xx := e^[1i*pi]"));
    lines.push_back(std::make_shared<std::string>("xx := re_sqrt(2)"));
    lines.push_back(std::make_shared<std::string>("re_sqrt(2)"));
    lines.push_back(std::make_shared<std::string>("cx_sqrt(2)"));
    lines.push_back(std::make_shared<std::string>("real(3i+5i*7.i)"));
    lines.push_back(std::make_shared<std::string>("imag(3i+5i*7.i)"));
    lines.push_back(std::make_shared<std::string>("conj(3i+5i*7.i)"));
    lines.push_back(std::make_shared<std::string>("abs(-7)"));
    lines.push_back(std::make_shared<std::string>("abs(1i+1)"));
    lines.push_back(std::make_shared<std::string>("op_to_mat(1i+1)"));
    lines.push_back(std::make_shared<std::string>("normalop_zeros()"));
    lines.push_back(std::make_shared<std::string>("normalop_print(normalop_zeros(),6)"));
    lines.push_back(std::make_shared<std::string>("d := normalop_diag(7.8, 3)"));
    lines.push_back(std::make_shared<std::string>("h := normalop_hop(7.2, 4, 5)"));
    lines.push_back(std::make_shared<std::string>("dh := d+h"));
    lines.push_back(std::make_shared<std::string>("normalop_print(dh, 6)"));
    lines.push_back(std::make_shared<std::string>("ELECTRON_DOMAIN := create_normal_domain(AC, CA, EG, GE)"));
    lines.push_back(std::make_shared<std::string>("ELECTRON_DOMAIN"));
    lines.push_back(std::make_shared<std::string>("EG"));
    lines.push_back(std::make_shared<std::string>("create_normal_domain(AC2, CA2, EG2, GE2)"));
    lines.push_back(std::make_shared<std::string>("EG2"));
    lines.push_back(std::make_shared<std::string>("h := normalop_hop(5, AC2, CA2)"));
    lines.push_back(std::make_shared<std::string>("d := normalop_diag(7.8, EG2)"));
    lines.push_back(std::make_shared<std::string>("normalop_diag(7.8, EG2)"));
    lines.push_back(std::make_shared<std::string>("normalop_print(h)"));
    lines.push_back(std::make_shared<std::string>("normalop_print(d)"));
    lines.push_back(std::make_shared<std::string>("z := normalop_zero(ELECTRON_DOMAIN)"));
    lines.push_back(std::make_shared<std::string>("normalop_print(z)"));

    onerut_parser::GlobalFunctionFactories::instance().put_cmath();
    onerut_parser::GlobalFunctionFactories::instance().put_onerut_functions();

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