#ifndef ONERUT_PARSER_IDENTIFIER
#define ONERUT_PARSER_IDENTIFIER

#include<onerut_parser/compile_result_deref.hpp>

namespace onerut_parser {

    class AbstractCompileResultRef {
    public:
        virtual CompileResultDeref get_compile_result_deref() const = 0;
        virtual ~AbstractCompileResultRef() = default;
    };

    // TODO: przerobić na szczegolny przypadek CompileResultConstRef.
    class ConstDoubleHolder : public AbstractCompileResultRef {
    public:
        ConstDoubleHolder(double value);
        CompileResultDeref get_compile_result_deref() const override;
        const double value;
    };

    class CompileResultConstRef : public AbstractCompileResultRef {
    public:
        CompileResultConstRef(std::u32string name, CompileResultDeref value);
        CompileResultDeref get_compile_result_deref() const override;
        std::u32string get_name() const;
    private:
        const std::u32string name;
        const CompileResultDeref value;
    };

    class CompileResultNotConstRef : public AbstractCompileResultRef {
    public:
        CompileResultNotConstRef(std::u32string name, CompileResultDeref value);
        CompileResultDeref get_compile_result_deref() const override;
        void set_compile_result(CompileResultDeref new_value);
        std::u32string get_name() const;
    private:
        const std::u32string name;
        CompileResultDeref value;
    };

}

#endif
