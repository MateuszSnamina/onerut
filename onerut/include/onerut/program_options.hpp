#ifndef ONERUT_PROGRAM_OPTIONS_HPP
#define ONERUT_PROGRAM_OPTIONS_HPP

#include<string>
#include<iostream>
#include<filesystem>

struct ProgramOptions {
    // Types:
    enum class ScriptType;
    // Data:
    std::filesystem::path script_file_path;    
    ScriptType script_type;
    unsigned n_max_iterations;
};

enum class ProgramOptions::ScriptType {
    Imperative,
    Declarative
};

std::ostream& operator<<(std::ostream&, ProgramOptions::ScriptType);

ProgramOptions grep_program_options(int argc, char** argv);

#endif 

