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
#include<onerut_parser/function_factory_container.hpp>
#include<onerut_parser/asset_utility.hpp>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/to_string.hpp>

#include<type_traits>


//--------------------------------------------

bool
execute_line(std::shared_ptr<const std::string> line) {
    // #########################################################################
    std::cout << esc::manip::bg_yellow << "Processsing "
            << esc::manip::blue << string_utils::StreamToGreek(*line) << esc::manip::color_default
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
    // #########################################################################
    const auto ast_source_head = onerut_parser::onerut_ast::to_ast_source(
            parsed_x3_info.ast_head,
            parsed_x3_info.input,
            parsed_x3_info.positions);
    // -------------------------------------------------------------------------
    //    const auto ast_source_ast_chart = ast_source_head->to_ast_chart();
    //    onerut_parser::print_ast_chart(parsed_x3_info.input, ast_source_ast_chart, , "[source ] ");
    // #########################################################################
    const auto ast_asset_head = ast_source_head->compile();
    // -------------------------------------------------------------------------
    const auto asset_ast_chart = ast_asset_head->to_ast_chart();
    onerut_parser::print_ast_chart(parsed_x3_info.input, asset_ast_chart, "[diagram] ");
    const auto asset_errors_chart = ast_asset_head->to_errors_chart();
    onerut_parser::print_errors_chart(parsed_x3_info.input, asset_errors_chart, "[errors ] ");
    // -------------------------------------------------------------------------
    onerut_parser::Asset asset = ast_asset_head->asset;
    if (onerut_parser::utility::is_unset_ref(asset)) {
        std::cout << "[receipt] Expression is an " << esc::manip::italic << "unset reference." << std::endl;
        const auto result_reference = *(asset.reference_or_empty());
        std::cout << "[receipt] Name = " << result_reference->get_name() << std::endl;
    } else if (asset.deref().is_compile_error()) {
        std::cout << "[receipt] Expression is an " << esc::manip::italic << "error." << std::endl;
        const auto error = *asset.deref().compile_error_or_empty();
        std::cout << "[receipt] Error message = " << error->what() << std::endl;
    } else if (asset.deref().is_given_type<onerut_scalar::Integer>()) {
        std::cout << "[receipt] Expression is an " << esc::manip::italic << "integer-number." << std::endl;
        const auto result_integer = *(asset.deref().typed_value_or_empty<onerut_scalar::Integer>());
        std::cout << "[receipt] Value = " << result_integer->value_integer() << std::endl;
    } else if (asset.deref().is_given_type<onerut_scalar::Real>()) {
        std::cout << "[receipt] Expression is a " << esc::manip::italic << "real-number." << std::endl;
        const auto result_real = *(asset.deref().typed_value_or_empty<onerut_scalar::Real>());
        std::cout << "[receipt] Value = " << result_real->value_real() << std::endl;
    } else if (asset.deref().is_given_type<onerut_scalar::Complex>()) {
        std::cout << "[receipt] Expression is a " << esc::manip::italic << "complex-number." << std::endl;
        const auto result_complex = *(asset.deref().typed_value_or_empty<onerut_scalar::Complex>());
        std::cout << "[receipt] Value = " << result_complex->value_complex() << std::endl;
    } else if (asset.deref().is_given_type<onerut_normal_operator::StateIndex>()) {
        std::cout << "[receipt] Expression is a " << esc::manip::italic << "normal-domain-state-index ." << std::endl;
        const auto state = *(asset.deref().typed_value_or_empty<onerut_normal_operator::StateIndex>());
        std::cout << "[receipt] Value = " << state->to_str() << std::endl;
    } else if (asset.deref().is_given_type<onerut_normal_operator::Domain>()) {
        std::cout << "[receipt] Expression is a " << esc::manip::italic << "normal-domain." << std::endl;
        const auto domain = *(asset.deref().typed_value_or_empty<onerut_normal_operator::Domain>());
        std::cout << "[receipt] Value = " << onerut_normal_operator::to_string(*domain) << std::endl;
    } else if (asset.deref().is_given_type<onerut_normal_operator::AbstractOperator>()) {
        std::cout << "[receipt] Expression is a " << esc::manip::italic << "normal-domain-operator" << esc::manip::reset << "." << std::endl;
        const auto op = *(asset.deref().typed_value_or_empty<onerut_normal_operator::AbstractOperator>());
        //std::cout << "[receipt] Operator domain = " << onerut_normal_operator::to_string(*op->get_domain()) << std::endl;
        std::cout << onerut_normal_operator::to_string(*op, "[receipt] ");
    } else {
        std::cout << "[receipt] Result is not an error nor a scalar." << std::endl;
    }
    std::cout << std::endl;
    return true;
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
    lines.push_back(std::make_shared<const std::string>("EG"));
    lines.push_back(std::make_shared<const std::string>("create_normal_domain(AC2_alpha_bcdefgh, CA2, EG2_gamma_2, GE2)"));
    lines.push_back(std::make_shared<const std::string>("EG2"));
    lines.push_back(std::make_shared<const std::string>("h := normalop_hop(5, AC2_alpha_bcdefgh, CA2)"));
    lines.push_back(std::make_shared<const std::string>("d := normalop_diag(70000000000000.8, GE2)"));
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