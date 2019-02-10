#ifndef ONERUT_PARSER_FUNCTION_ABSTRACT
#define ONERUT_PARSER_FUNCTION_ABSTRACT

#include<vector>

#include<onerut_parser/compile_result.hpp>

namespace onerut_parser {

    class AbstractFunction {
    public:
        virtual CompileResult get_compile_result(std::vector<CompileResult> argv) const = 0;
        virtual ~AbstractFunction() = default;
    };

    // ---------------------------------------------------------------------------

    class UnaryFunction : public AbstractFunction {
    public:
        CompileResult get_compile_result(std::vector<CompileResult> argv) const final;
        virtual CompileResult get_compile_result(CompileResult arg) const = 0;
    };

    class BinaryFunction : public AbstractFunction {
    public:
        CompileResult get_compile_result(std::vector<CompileResult> argv) const final;
        virtual CompileResult get_compile_result(CompileResult first_arg, CompileResult second_arg) const = 0;
    };

    // ---------------------------------------------------------------------------

}

#endif
