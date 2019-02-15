#include<onerut_parser/function_factory_abstract.hpp>

namespace onerut_parser {

    CompileResult UnaryFunctionFactory::make_function_otherwise_make_error(std::vector<CompileResult> argv) const {
        if (argv.size() != 1)
            return CompileResult::from_compile_error(std::make_shared<WrongNumberOfArgumentsError>());
        return make_function_otherwise_make_error(argv[0]);
    }

    CompileResult BinaryFunctionFactory::make_function_otherwise_make_error(std::vector<CompileResult> argv) const {
        if (argv.size() != 2)
            return CompileResult::from_compile_error(std::make_shared<WrongNumberOfArgumentsError>());
        return make_function_otherwise_make_error(argv[0], argv[1]);
    }

}

