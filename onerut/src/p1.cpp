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
#include<onerut_scalar/scalar.hpp>

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

    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;

    auto o1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(4.6, 1, 3);
    auto o2 = std::make_shared<onerut_operator::HopOperator<unsigned>>(2.2, 1, 2);
    auto o3 = std::make_shared<onerut_operator::ScalledOperator<unsigned>>(2.0, o1);

    auto o4 = std::make_shared<onerut_operator::HopOperator<unsigned>>(3.2, 2, 1);
    auto o5 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(10, 1);
    auto o6 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(19, 2);
    auto o7 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(7, 0);
    OpPtrT o8_first_arg = o4;
    std::vector<OpPtrT> o8_other_argv({o5, o6, o7});
    std::vector<char> o8_opv({'+', '-', '-'});
    auto o8 = std::make_shared<onerut_operator::OpPlusMinusOperator<unsigned>>(o8_first_arg, o8_other_argv, o8_opv);

    OpPtrT o9_first_arg = o1;
    std::vector<OpPtrT> o9_other_argv({o2, o3});
    std::vector<char> o9_opv({'-', '-'});
    auto o9 = std::make_shared<onerut_operator::OpPlusMinusOperator<unsigned>>(o9_first_arg, o9_other_argv, o9_opv);

    std::vector<OpPtrT> o20_argv({o8, o9});
    auto o20 = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(o20_argv);

    std::vector<OpPtrT> o21_argv({o2, o8, o9, o1});
    auto o21 = std::make_shared<onerut_operator::OpProdOperator<unsigned>>(o21_argv);


    //arma::mat M = ;
    std::cout << onerut_operator::to_mat(*o1, 4) << std::endl;
    std::cout << onerut_operator::to_mat(*o2, 4) << std::endl;
    std::cout << onerut_operator::to_mat(*o3, 4) << std::endl;
    std::cout << "o7:" << std::endl;
    std::cout << onerut_operator::to_mat(*o7, 4) << std::endl;
    std::cout << "o8:" << std::endl;
    std::cout << onerut_operator::to_mat(*o8, 4) << std::endl;
    std::cout << "o9:" << std::endl;
    std::cout << onerut_operator::to_mat(*o9, 4) << std::endl;
    std::cout << "o20:" << std::endl;
    std::cout << onerut_operator::to_mat(*o20, 4) << std::endl;
    std::cout << "o8 * o9:" << std::endl;
    std::cout << onerut_operator::to_mat(*o8, 4) * onerut_operator::to_mat(*o9, 4) << std::endl;

    std::cout << "o21:" << std::endl;
    std::cout << onerut_operator::to_mat(*o21, 4) << std::endl;
    std::cout << "o2 * o8 * o9 * o1:" << std::endl;
    std::cout << onerut_operator::to_mat(*o2, 4) * onerut_operator::to_mat(*o8, 4) * onerut_operator::to_mat(*o9, 4) * onerut_operator::to_mat(*o1, 4) << std::endl;
    return;

    //std::string input = "  _alg(_67j, foo(  7  , 8 ) , (xx2s) ) kota* 56.8 ";
    //const std::string input = "  3.0^6@t+_alg((5->4-7/foo(6)), 8.9*ola::ala,-pi+9,-7+9)*(-(9))+(-(9.0)+1) ";
    //std::cout << (13 / 2 * 0.5 + (-(7.8 * (5 + 5 * 7)) + 8. + -.8) / 9) << std::endl;

    std::vector<std::shared_ptr < std::string>> lines;
    lines.push_back(std::make_shared < std::string>("x:=(2+4*3)+pi/2"));
    lines.push_back(std::make_shared < std::string>("x+7"));
    lines.push_back(std::make_shared < std::string>("x:=40"));
    lines.push_back(std::make_shared < std::string>("x+4"));
    lines.push_back(std::make_shared < std::string>("sqrt(4.0)"));
    lines.push_back(std::make_shared < std::string>("max(3,2)"));
    lines.push_back(std::make_shared < std::string>("sin(pi/4)/sqrt(2)"));
    lines.push_back(std::make_shared < std::string>("3^2"));
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