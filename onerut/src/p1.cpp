#include<iostream>
#include<fstream>
#include<filesystem>

#include<esc/esc_manip.hpp>
//#include<string_utils/greek_support.hpp>

#include<onerut/line_processor.hpp>
#include<onerut/line_preprocessor.hpp>

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
        const auto line_ptr = std::make_shared<const std::string>(line);
        lines.push_back(line_ptr);
    }
    return lines;
}

void execute_imparative_script(const std::vector<std::shared_ptr<const std::string>>&lines) {
    process_imperative_lines(lines);
    //execute_script_lines(lines);
    //return execute_script_lines(lines);
}

void execute_declarative_script(const std::vector<std::shared_ptr<const std::string>>&lines) {
    process_declarative_lines(lines);
    //execute_script_lines(lines);
    //return execute_script_lines(lines);
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
    //lines.push_back(std::make_shared<const std::string>("mean_in_eigenstate(eye(custom_domain(xx0, yy0)), eigs(eye(custom_domain(xx1, yy2)), 1), 0)"));
    lines.push_back(std::make_shared<const std::string>("pa := parameter(4)"));
    lines.push_back(std::make_shared<const std::string>("VALUE(pa)"));
    lines.push_back(std::make_shared<const std::string>("pa -> 7"));
    lines.push_back(std::make_shared<const std::string>("VALUE(pa)"));
    lines.push_back(std::make_shared<const std::string>("pa :: 0.2"));
    lines.push_back(std::make_shared<const std::string>("VALUE(pa)"));
    lines.push_back(std::make_shared<const std::string>("pa+5"));
    lines.push_back(std::make_shared<const std::string>("VALUE(pa+5)"));
    execute_imparative_script(lines);
}

int main(int argc, char** argv) {
    if (argc == 2) {
        std::cout << "enter script mode" << std::endl;
        const std::filesystem::path file_path(argv[1]);
        std::cout << "file path: " << file_path << std::endl;
        auto lines = preprocess_line(load_script_lines_from_file(file_path));
        execute_imparative_script(lines);
    } else {
        temp_testing();
    }
}