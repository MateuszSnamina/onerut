#include<iostream>
#include<fstream>
#include<iomanip>
#include<optional>
#include<filesystem>

#include<esc/esc_manip.hpp>
#include<string_utils/string_span.hpp>
#include<string_utils/greek_support.hpp>
#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_source.hpp>
#include<onerut_parser/ast_compile_result.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_parser/function_factory_global.hpp>
#include<onerut_parser/function_factory_abstract.hpp>
#include<onerut_parser/compile_result_utility.hpp>

#include<onerut_scalar/scalar_abstract.hpp>

#include<onerut_operator/operator.hpp>

#include<type_traits>

//--------------------------------------------

class NormalOperatorZerosFunctionFactory : public onerut_parser::NaryFunctionFactory<0> {

    onerut_parser::CompileResult make_function_otherwise_make_error(std::array<onerut_parser::CompileResult, 0> args_compile_result) const override {
        using AbstractOperatorT = onerut_operator::AbstractOperator<unsigned>;
        using OperatorT = onerut_operator::ZeroOperator<unsigned>;
        return onerut_parser::CompileResult::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>());
    }

};

class NormalOperatorDiagFunctionFactory : public onerut_parser::NaryFunctionFactory<2> {

    onerut_parser::CompileResult make_function_otherwise_make_error(std::array<onerut_parser::CompileResult, 2> args_compile_result) const override {
        const auto & arg0_compile_result_deref = args_compile_result[0].dereference();
        const auto & arg1_compile_result_deref = args_compile_result[1].dereference();
        if (!arg0_compile_result_deref.is_either_value_or_type())
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::CompileArgumentsError>());
        if (!arg1_compile_result_deref.is_either_value_or_type())
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::CompileArgumentsError>());
        if (!onerut_parser::utility::is_real_or_integer(arg0_compile_result_deref))
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::ArgumentMismatchError>());
        if (!onerut_parser::utility::is_integer(arg1_compile_result_deref))
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::ArgumentMismatchError>());
        const auto value = onerut_parser::utility::to_real(arg0_compile_result_deref);
        const auto site = onerut_parser::utility::to_integer(arg1_compile_result_deref);
        using AbstractOperatorT = onerut_operator::AbstractOperator<unsigned>;
        using OperatorT = onerut_operator::DiagOperator<unsigned>;
        return onerut_parser::CompileResult::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(value->value_real(), static_cast<unsigned> (site->value_integer())));
    }

};

class NormalOperatorHopFunctionFactory : public onerut_parser::NaryFunctionFactory<3> {

    onerut_parser::CompileResult make_function_otherwise_make_error(std::array<onerut_parser::CompileResult, 3> args_compile_result) const override {
        const auto & arg0_compile_result_deref = args_compile_result[0].dereference();
        const auto & arg1_compile_result_deref = args_compile_result[1].dereference();
        const auto & arg2_compile_result_deref = args_compile_result[2].dereference();
        if (!arg0_compile_result_deref.is_either_value_or_type())
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::CompileArgumentsError>());
        if (!arg1_compile_result_deref.is_either_value_or_type())
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::CompileArgumentsError>());
        if (!arg2_compile_result_deref.is_either_value_or_type())
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::CompileArgumentsError>());
        if (!onerut_parser::utility::is_real_or_integer(arg0_compile_result_deref))
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::ArgumentMismatchError>());
        if (!onerut_parser::utility::is_integer(arg1_compile_result_deref))
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::ArgumentMismatchError>());
        if (!onerut_parser::utility::is_integer(arg2_compile_result_deref))
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::ArgumentMismatchError>());
        const auto value = onerut_parser::utility::to_real(arg0_compile_result_deref);
        const auto site1 = onerut_parser::utility::to_integer(arg1_compile_result_deref);
        const auto site2 = onerut_parser::utility::to_integer(arg2_compile_result_deref);
        using AbstractOperatorT = onerut_operator::AbstractOperator<unsigned>;
        using OperatorT = onerut_operator::HopOperator<unsigned>;
        return onerut_parser::CompileResult::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(
                value->value_real(),
                static_cast<unsigned> (site1->value_integer()),
                static_cast<unsigned> (site2->value_integer())
                ));
    }

};

class NormalOperatorPrintFactory : public onerut_parser::NaryFunctionFactory<2> {

    onerut_parser::CompileResult make_function_otherwise_make_error(std::array<onerut_parser::CompileResult, 2> args_compile_result) const override {
        const auto & arg0_compile_result_deref = args_compile_result[0].dereference();
        const auto & arg1_compile_result_deref = args_compile_result[1].dereference();
        if (!arg0_compile_result_deref.is_either_value_or_type())
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::CompileArgumentsError>());
        if (!arg1_compile_result_deref.is_either_value_or_type())
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::CompileArgumentsError>());
        if (!onerut_parser::utility::is_normal_operator(arg0_compile_result_deref))
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::ArgumentMismatchError>());
        if (!onerut_parser::utility::is_integer(arg1_compile_result_deref))
            return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::ArgumentMismatchError>());
        const auto normal_operator = onerut_parser::utility::to_normal_operator(arg0_compile_result_deref);
        const auto dim = onerut_parser::utility::to_integer(arg1_compile_result_deref);
        const arma::mat M = onerut_operator::to_mat(*normal_operator, dim->value_integer());
        std::cout << M << std::endl;

        return args_compile_result[0];
    }

};

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
    onerut_parser::print_chart(parsed_x3_info.input, ast_compile_result_chart, "[diagram] ");
    // -------------------------------------------------------------------------
    onerut_parser::CompileResult compile_result = ast_compile_result_head->compile_result;

    if (compile_result.dereference().is_compile_error()) {
        std::cout << "[receipt] Expression is an error." << std::endl;
        const auto error = *compile_result.dereference().compile_error_or_empty();
        std::cout << "[receipt] Error message = " << error->what() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Integer>()) {
        std::cout << "[receipt] Expression is an integer number." << std::endl;
        const auto result_integer = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Integer>());
        std::cout << "[receipt] Value = " << result_integer->value_integer() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Real>()) {
        std::cout << "[receipt] Expression is a real number." << std::endl;
        const auto result_real = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Real>());
        std::cout << "[receipt] Value = " << result_real->value_real() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Complex>()) {
        std::cout << "[receipt] Expression is a complex number." << std::endl;
        const auto result_complex = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Complex>());
        std::cout << "[receipt] Value = " << result_complex->value_complex() << std::endl;
    } else {
        std::cout << "[receipt] Result is not an error nor a scalar." << std::endl;
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
    onerut_parser::GlobalFunctionFactories::instance().put_cmath();

    return execute_script_lines(lines);
}

void temp_testing() {

    //    using fp = double(*)(int);
    // using U = typename std::result_of < decltype(fp)>::type;
    //using U = typename CallableReturnType<fp,int>::ReturnType;
    //using U = typename CallableReturnType<F, int>::ReturnType;
    //std::cout << std::is_same<U, int>::value << std::endl;

    //exit(10);

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
    lines.push_back(std::make_shared<std::string>("normalop_print(normalop_diag(7.8, 3),6)"));
    lines.push_back(std::make_shared<std::string>("normalop_print(normalop_hop(7.2, 4, 5),6)"));

    onerut_parser::GlobalIdentifiers::instance().put_e();
    onerut_parser::GlobalIdentifiers::instance().put_pi();
    onerut_parser::GlobalFunctionFactories::instance().put_cmath();

    
    onerut_parser::GlobalFunctionFactories::instance().force_put("normalop_zeros", std::make_unique<NormalOperatorZerosFunctionFactory>());
    onerut_parser::GlobalFunctionFactories::instance().force_put("normalop_diag", std::make_unique<NormalOperatorDiagFunctionFactory>());
    onerut_parser::GlobalFunctionFactories::instance().force_put("normalop_hop", std::make_unique<NormalOperatorHopFunctionFactory>());
    onerut_parser::GlobalFunctionFactories::instance().force_put("normalop_print", std::make_unique<NormalOperatorPrintFactory>());
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