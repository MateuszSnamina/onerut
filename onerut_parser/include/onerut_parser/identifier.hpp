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
    class ConstRealHolder : public AbstractCompileResultRef {
    public:
        ConstRealHolder(double value);
        CompileResultDeref get_compile_result_deref() const override;
        const double value;
    };

    class CompileResultConstRef : public AbstractCompileResultRef {
    public:
        CompileResultConstRef(std::string name, CompileResultDeref value);
        CompileResultDeref get_compile_result_deref() const override;
        std::string get_name() const;
    private:
        const std::string name;
        const CompileResultDeref value;
    };

    class CompileResultNotConstRef : public AbstractCompileResultRef {
    public:
        CompileResultNotConstRef(std::string name, CompileResultDeref value);
        CompileResultDeref get_compile_result_deref() const override;
        void set_compile_result(CompileResultDeref new_value);
        std::string get_name() const;
    private:
        const std::string name;
        CompileResultDeref value;
    };

}

#endif
