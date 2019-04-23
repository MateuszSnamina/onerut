#include<onerut/line_processor.hpp>
#include<onerut/line_preprocessor.hpp>
#include<onerut/execute_script.hpp>

void
execute_imparative_script(const std::vector<std::shared_ptr<const std::string>>&lines) {
    process_imperative_lines(preprocess_line(lines));
    //execute_script_lines(lines);
    //return execute_script_lines(lines);
}

void
execute_declarative_script(const std::vector<std::shared_ptr<const std::string>>&lines) {
    process_declarative_lines(preprocess_line(lines));
    //execute_script_lines(lines);
    //return execute_script_lines(lines);
}
