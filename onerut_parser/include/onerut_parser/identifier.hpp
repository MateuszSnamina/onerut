#ifndef ONERUT_PARSER_IDENTIFIER
#define ONERUT_PARSER_IDENTIFIER

#include<onerut_parser/compile_result.hpp>

namespace onerut_parser {

    class AbstractCompileResultHolder {
    public:
        virtual CompileResult get_compile_result() const = 0;
        virtual ~AbstractCompileResultHolder() = default;
    };

    class ConstDoubleHolder : public AbstractCompileResultHolder {
    public:
        ConstDoubleHolder(double value);
        CompileResult get_compile_result() const override;
        const double value;
    };

    class ConstCompileResultRef : public AbstractCompileResultHolder {
    public:
        ConstCompileResultRef(CompileResult value);
        CompileResult get_compile_result() const override;
        const CompileResult value;
    };

    class CompileResultRef : public AbstractCompileResultHolder {
    public:
        CompileResultRef(CompileResult value);
        CompileResult get_compile_result() const override;
        void set_compile_result(CompileResult new_value);
        CompileResult value;
    };

}

#endif
