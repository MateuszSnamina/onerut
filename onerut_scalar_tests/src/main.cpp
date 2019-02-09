#include<iostream>
#include<boost/program_options.hpp>
#include<gtest/gtest.h>

#include<onerut_operator_tests/global_flags.hpp>

namespace {

    void emit_help(std::ostream& s,
            const boost::program_options::options_description& desc) {
        s << desc << std::endl;
    }

} // namespace

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    boost::program_options::options_description desc("Options");
    desc.add_options()
            // --help, -h:
            ("help,h", "Print help messages")
            // --verbose, -h:
            ("verbose,v",
            boost::program_options::bool_switch(
            &onerut_verbose)
            ->default_value(false),
            "Run tests in verbose mode.");
    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(
                boost::program_options::command_line_parser(argc, argv)
                .options(desc)
                .run(),
                vm); // may throw
        if (vm.count("help")) {
            emit_help(std::cout, desc);
            exit(0);
        }
        // sets auto variables (eq. class_specification_file_path),
        // throw is required variable is missing:
        boost::program_options::notify(vm); // may throw
    } catch (boost::program_options::error& e) {
        std::cerr << "[GLOBAL ERROR] [PROGRAM OPTIONS ERROR]: " << e.what()
                << std::endl;
        std::cerr << std::endl;
        emit_help(std::cerr, desc);
        exit(1);
    }

    return RUN_ALL_TESTS();
}

