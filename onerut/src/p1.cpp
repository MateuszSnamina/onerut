#include<iostream>
#include<fstream>
#include<filesystem>

#include<esc/esc_manip.hpp>

//#include<string_utils/greek_support.hpp>

#include<onerut/execute_script.hpp>
#include<onerut/program_options.hpp>

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

int main(int argc, char** argv) {
    ProgramOptions program_options = grep_program_options(argc, argv);
    std::cout << "[INFO   ] [PROGRAM_OPTIONS] script_file_path = " << program_options.script_file_path << std::endl;
    std::cout << "[INFO   ] [PROGRAM_OPTIONS] script_type      = " << program_options.script_type << std::endl;
    std::cout << "[INFO   ] [PROGRAM_OPTIONS] n_max_iterations = " << program_options.n_max_iterations << std::endl;
    // -------------------------------------------------------------------------
    const auto lines = load_script_lines_from_file(program_options.script_file_path);
    if (program_options.script_type == ProgramOptions::ScriptType::Declarative) {
        execute_declarative_script(lines, program_options.n_max_iterations);
    } else {
        execute_imperative_script(lines);
    }
}