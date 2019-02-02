#include<onerut_parser/function.hpp>

namespace onerut_parser {

    CompileResult UnaryFunction::get_compile_result(std::vector<CompileResult> argv) const {
        if (argv.size() != 1)
            return CompileResult::from_compile_error(std::make_shared<WrongNumberOfArgumentsError>());
        return get_compile_result(argv[0]);
    }

    CompileResult BinaryFunction::get_compile_result(std::vector<CompileResult> argv) const {
        if (argv.size() != 2)
            return CompileResult::from_compile_error(std::make_shared<WrongNumberOfArgumentsError>());
        return get_compile_result(argv[0], argv[1]);
    }

}

