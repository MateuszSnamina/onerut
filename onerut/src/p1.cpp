#include<cctype> // to script.cpp
#include<iterator> // to script.cpp

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

#include<onerut_parser/request_imperative.hpp>
#include<onerut_parser/request_print_value.hpp>

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
    // *************  Requests stage:        ***********************************
    // *************************************************************************
    if (const auto request = asset.deref().typed_value_or_empty<onerut_parser::ImperativeRequest>()) {
        (*request)->exec();
    }
    if (const auto request = asset.deref().typed_value_or_empty<onerut_parser::PrintValueRequest>()) {
        (*request)->print(std::cout, "[request] ");
    }
    // *************************************************************************
    std::cout << std::endl;
    return true; // TODO
}

const std::string preprocesor(const std::string& line) {
    auto it = std::find_if(line.cbegin(), line.cend(),
            [](char ch) {
                return ch == '#';
            });
    it = std::find_if(std::make_reverse_iterator(it), line.crend(),
            [](char ch) {
                return !std::isspace(ch);
            }).base();
    return {line.begin(), it};
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
        const auto preprocesed_line = preprocesor(line);
        const auto line_ptr = std::make_shared<const std::string>(preprocesed_line);
        if (!preprocesed_line.empty())
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
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    return execute_script_lines(lines);
}

void temp_testing() {
    std::vector<std::shared_ptr<const std::string> > lines;
    //    lines.push_back(std::make_shared<const std::string>("x:=(2+4*3)+pi/2"));
    //    lines.push_back(std::make_shared<const std::string>("x+7"));
    //    lines.push_back(std::make_shared<const std::string>("x:=40"));
    //    lines.push_back(std::make_shared<const std::string>("x+4"));
    //    lines.push_back(std::make_shared<const std::string>("sqrt(4.0)"));
    //    lines.push_back(std::make_shared<const std::string>("max(3,2)"));
    //    lines.push_back(std::make_shared<const std::string>("sin(pi/4)/sqrt(2)"));
    //    lines.push_back(std::make_shared<const std::string>("3^2"));
    //    lines.push_back(std::make_shared<const std::string>("5i"));
    //    lines.push_back(std::make_shared<const std::string>("5i+6 + 7i"));
    //    lines.push_back(std::make_shared<const std::string>("conj(3i+5i*7.i)"));
    //    lines.push_back(std::make_shared<const std::string>("pow(2i,2)"));
    //    lines.push_back(std::make_shared<const std::string>("cx_pow(2i,2)"));
    //    lines.push_back(std::make_shared<const std::string>("pow(2,2)"));
    //    lines.push_back(std::make_shared<const std::string>("pow(2,2.0)"));
    //    lines.push_back(std::make_shared<const std::string>("pow(2,2.2)"));
    //    lines.push_back(std::make_shared<const std::string>("sqrt(2)"));
    //    lines.push_back(std::make_shared<const std::string>("sqrt(2.0)"));
    //    lines.push_back(std::make_shared<const std::string>("sqrt(sqrt(2)*1i)"));
    //    lines.push_back(std::make_shared<const std::string>("norm(sqrt(sqrt(2)*1i))"));
    //    lines.push_back(std::make_shared<const std::string>("re_sqrt(2)"));
    //    lines.push_back(std::make_shared<const std::string>("cx_sqrt(2)"));
    //    lines.push_back(std::make_shared<const std::string>("new z := sqrt(2i)"));
    //    lines.push_back(std::make_shared<const std::string>("re := real(z)"));
    //    lines.push_back(std::make_shared<const std::string>("im := imag(z)"));
    //    lines.push_back(std::make_shared<const std::string>("xx := re+im+ pi + kupi + (2*7+7)+ alpha*9 + piwo*(3*8+Ups+ups+Up+up) + pi"));
    //    lines.push_back(std::make_shared<const std::string>("xx := e^[1i*pi]"));
    //    lines.push_back(std::make_shared<const std::string>("xx := re_sqrt(2)"));
    //    lines.push_back(std::make_shared<const std::string>("re_sqrt(2)"));
    //    lines.push_back(std::make_shared<const std::string>("cx_sqrt(2)"));
    //    lines.push_back(std::make_shared<const std::string>("real(3i+5i*7.i)"));
    //    lines.push_back(std::make_shared<const std::string>("imag(3i+5i*7.i)"));
    //    lines.push_back(std::make_shared<const std::string>("conj(3i+5i*7.i)"));
    //    lines.push_back(std::make_shared<const std::string>("abs(-7)"));
    //    lines.push_back(std::make_shared<const std::string>("abs(1i+1)"));
    //    lines.push_back(std::make_shared<const std::string>("op_to_mat(1i+1)"));
    //    lines.push_back(std::make_shared<const std::string>("ELECTRON_DOMAIN := normal_domain(AC, CA, EG, GE)"));
    //    lines.push_back(std::make_shared<const std::string>("MUON_DOMAIN := normal_domain(AC1, CA1, EG1, GE1)"));
    //    lines.push_back(std::make_shared<const std::string>("ELECTRON_DOMAIN"));
    //    lines.push_back(std::make_shared<const std::string>("op1 :=  hop(5, AC, CA)"));
    //    lines.push_back(std::make_shared<const std::string>("op2 :=  hop(3, CA, EG)"));
    //    lines.push_back(std::make_shared<const std::string>("op1 * op2"));
    //    lines.push_back(std::make_shared<const std::string>("op2 * op1"));
    //    lines.push_back(std::make_shared<const std::string>("S1 := state_index(ELECTRON_DOMAIN,0)"));
    //    lines.push_back(std::make_shared<const std::string>("S2 := state_index(ELECTRON_DOMAIN,1)"));
    //    lines.push_back(std::make_shared<const std::string>("S3 := state_index(MUON_DOMAIN,1)"));
    //    lines.push_back(std::make_shared<const std::string>("S4 := state_index(MUON_DOMAIN,2)"));
    //    lines.push_back(std::make_shared<const std::string>("op3 :=  hop(400, S1, S2)"));
    //    lines.push_back(std::make_shared<const std::string>("op1"));
    //    lines.push_back(std::make_shared<const std::string>("4* op1 + op3 + op2"));
    //    lines.push_back(std::make_shared<const std::string>("op4 :=  hop(400, S4, S3)"));
    //    lines.push_back(std::make_shared<const std::string>("4* op1 + op3 + op4+ op2"));
    //    lines.push_back(std::make_shared<const std::string>("-(4* op1 + op3 + op4+ op2)"));
    //    lines.push_back(std::make_shared<const std::string>("4* op1 + op3 + op2"));
    //    lines.push_back(std::make_shared<const std::string>("-(4* op1 + op3 + op2)"));
    //    lines.push_back(std::make_shared<const std::string>("SQW := spin_domain(5)"));
    //    lines.push_back(std::make_shared<const std::string>("S5 := state_index(SQW,2)"));
    //    lines.push_back(std::make_shared<const std::string>("S6 := state_index(SQW,3)"));
    //    lines.push_back(std::make_shared<const std::string>("S6 := Sz(SQW) + hop(10.6,S5,S6)"));
    //    lines.push_back(std::make_shared<const std::string>("OSCILLATOR_SPACR := oscillator_domain(5)"));
    //    lines.push_back(std::make_shared<const std::string>("cr := cr(OSCILLATOR_SPACR)"));
    //    lines.push_back(std::make_shared<const std::string>("an := an(OSCILLATOR_SPACR)"));
    //    lines.push_back(std::make_shared<const std::string>("x  := (1/sqrt(2)) * ( cr + an)"));
    //    lines.push_back(std::make_shared<const std::string>("ip := (1/sqrt(2)) * (-cr + an)"));
    //    lines.push_back(std::make_shared<const std::string>("H1 := (1./2)*(x*x - ip*ip)"));
    //    lines.push_back(std::make_shared<const std::string>("n := cr * an"));
    //    lines.push_back(std::make_shared<const std::string>("H2 := cr * an + 1/2 * eye(OSCILLATOR_SPACR)"));

    //    lines.push_back(std::make_shared<const std::string>("EL_DOMAIN := custom_domain(E0, E1)"));
    //    lines.push_back(std::make_shared<const std::string>("MU_DOMAIN := custom_domain(M0, M1, M2)"));
    //    lines.push_back(std::make_shared<const std::string>("TA_DOMAIN := custom_domain(T0, T1)"));
    //    lines.push_back(std::make_shared<const std::string>("DOMAIN3 := kron_domain(EL_DOMAIN, MU_DOMAIN, TA_DOMAIN)"));
    //    lines.push_back(std::make_shared<const std::string>("VALUE(DOMAIN3)"));
    //    lines.push_back(std::make_shared<const std::string>("E3 := eye(DOMAIN3)"));
    //    lines.push_back(std::make_shared<const std::string>("VALUE(E3)"));
    //    lines.push_back(std::make_shared<const std::string>("DOMAIN2 := kron_domain(EL_DOMAIN, MU_DOMAIN)"));
    //    lines.push_back(std::make_shared<const std::string>("E2 := eye(DOMAIN2)"));
    //    lines.push_back(std::make_shared<const std::string>("VALUE(DOMAIN2)"));
    //    lines.push_back(std::make_shared<const std::string>("VALUE(E2)"));
    //    lines.push_back(std::make_shared<const std::string>("kron_placeholders(DOMAIN2)"));
    //    lines.push_back(std::make_shared<const std::string>("kron_placeholders(DOMAIN2,xx)"));
    //    lines.push_back(std::make_shared<const std::string>("kron_placeholders(DOMAIN2,xx,yy)"));
    //    lines.push_back(std::make_shared<const std::string>("kron_placeholders(DOMAIN2,xx,yy)"));
    //    lines.push_back(std::make_shared<const std::string>("kron_placeholders(DOMAIN2,xxx,yyy,zzz)"));
    //    lines.push_back(std::make_shared<const std::string>("kron_placeholders(DOMAIN2,4,5)"));
    //    lines.push_back(std::make_shared<const std::string>("xx"));
    //    lines.push_back(std::make_shared<const std::string>("yy"));
    //    lines.push_back(std::make_shared<const std::string>("VALUE(xx)"));
    //    lines.push_back(std::make_shared<const std::string>("VALUE(yy)"));
    //    lines.push_back(std::make_shared<const std::string>("at(E2, yy)"));
    //    lines.push_back(std::make_shared<const std::string>("EYE_EL:= eye(EL_DOMAIN)"));
    //    lines.push_back(std::make_shared<const std::string>("EYE_MU:= eye(MU_DOMAIN)"));
    //    lines.push_back(std::make_shared<const std::string>("at(E2, yy)"));
    //    lines.push_back(std::make_shared<const std::string>("at(EYE_EL, yy)"));
    //    lines.push_back(std::make_shared<const std::string>("EEE := at(EYE_MU, yy)"));
    //    lines.push_back(std::make_shared<const std::string>(" VALUE(EEE)"));
    lines.push_back(std::make_shared<const std::string>("mean_in_eigenstate(eye(custom_domain(xx0, yy0)), eigs(eye(custom_domain(xx1, yy2)), 1), 0)"));

    onerut_parser::FunctionFactoryContainer::global_instance().put_all();

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