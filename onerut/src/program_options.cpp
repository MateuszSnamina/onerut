#include <boost/program_options.hpp>
#include <iostream>

#include <onerut/program_options.hpp>

namespace {

    void emit_help(
            std::ostream& s,
            const boost::program_options::options_description& desc) {
        s << "Program: onerut" << std::endl;
        s << desc << std::endl;
    }
} // namespace

ProgramOptions grep_program_options(int argc, char** argv) {
    boost::program_options::options_description desc("CLI options");
    desc.add_options()
            // --help, -h:
            ("help,h",
            "Print help messages.")
            // --script-file-path:
            ("script-file-path",
            boost::program_options::value<std::string>()->required(),
            "The script file path.")
            // --n_max_iterations, -n:
            ("n_max_iterations,n",
            boost::program_options::value<unsigned>()->default_value(10u),
            "The number of iterations (applies to the declarative mode).")
            // --imperative, -i:
            ("imperative,i",
            boost::program_options::bool_switch(),
            "Treat the script as an imperative script (if switch is not given the script is treated as declarative).");
    boost::program_options::positional_options_description p;
    p.add("script-file-path", 1);
    // -------------------------------------------------------------------------
    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(
                boost::program_options::command_line_parser(argc, argv).options(desc).positional(p).run(),
                vm); // may throw
        if (vm.count("help")) {
            emit_help(std::cout, desc);
            exit(0);
        }
        // sets auto variables (eq. class_specification_file_path),
        // throw is required variable is missing:
        boost::program_options::notify(vm); // may throw
    } catch (boost::program_options::error& e) {
        std::cerr << "[GLOBAL ERROR] [PROGRAM OPTIONS ERROR]: " << e.what() << std::endl;
        std::cerr << std::endl;
        emit_help(std::cerr, desc);
        exit(1);
    }
    // -------------------------------------------------------------------------
    ProgramOptions program_options;
    program_options.script_file_path = std::experimental::filesystem::path(vm["script-file-path"].as<std::string>());
    program_options.script_type = vm["imperative"].as<bool>() ? ProgramOptions::ScriptType::Imperative : ProgramOptions::ScriptType::Declarative;
    program_options.n_max_iterations = vm["n_max_iterations"].as<unsigned>();
    return program_options;
}

std::ostream& operator<<(std::ostream& stream, ProgramOptions::ScriptType script_type) {
    switch (script_type) {
        case ProgramOptions::ScriptType::Imperative:
            stream << "imperative-script";
            break;
        case ProgramOptions::ScriptType::Declarative:
            stream << "declarative-script";
            break;
        default:
            stream << "invalid-script";
    }
    return stream;
}