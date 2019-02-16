#ifndef ONERUT_PARSER_FUNCTION_ABSTRACT
#define ONERUT_PARSER_FUNCTION_ABSTRACT

#include<array>
#include<vector>

#include<onerut_parser/compile_result.hpp>

namespace onerut_parser {

    class AbstractFunctionFactory {
    public:
        virtual CompileResult make_function_otherwise_make_error(std::vector<CompileResult> argv) const = 0; //TODO const vector&
        virtual ~AbstractFunctionFactory() = default;
    };
   
    // ---------------------------------------------------------------------------
    // ---------------------------------------------------------------------------

    template<unsigned nary>
    class NaryFunctionFactory : public AbstractFunctionFactory {
    public:
        CompileResult make_function_otherwise_make_error(std::vector<CompileResult> argv) const final;
        virtual CompileResult make_function_otherwise_make_error(std::array<CompileResult, nary> args) const = 0;
    };

    template<unsigned nary>
    CompileResult NaryFunctionFactory<nary>::make_function_otherwise_make_error(std::vector<CompileResult> argv) const {
        if (argv.size() != nary)
            return CompileResult::from_compile_error(std::make_shared<WrongNumberOfArgumentsError>());
        std::array<CompileResult, nary> args_array;
        std::copy(cbegin(argv), cend(argv), begin(args_array));
        return make_function_otherwise_make_error(args_array);
    }

}

#endif
