#ifndef ONERUT_PARSER_FUNCTION_ABSTRACT
#define ONERUT_PARSER_FUNCTION_ABSTRACT

#include<vector>

#include<onerut_parser/compile_result.hpp>

namespace onerut_parser {

    class AbstractFunctionFactory {
    public:
        virtual CompileResult make_function_otherwise_make_error(std::vector<CompileResult> argv) const = 0;
        virtual ~AbstractFunctionFactory() = default;
    };

    // ---------------------------------------------------------------------------

    class UnaryFunctionFactory : public AbstractFunctionFactory {
    public:
        CompileResult make_function_otherwise_make_error(std::vector<CompileResult> argv) const final;
        virtual CompileResult make_function_otherwise_make_error(CompileResult arg) const = 0;
    };

    class BinaryFunctionFactory : public AbstractFunctionFactory {
    public:
        CompileResult make_function_otherwise_make_error(std::vector<CompileResult> argv) const final;
        virtual CompileResult make_function_otherwise_make_error(CompileResult first_arg, CompileResult second_arg) const = 0;
    };

    // ---------------------------------------------------------------------------

}

#endif
