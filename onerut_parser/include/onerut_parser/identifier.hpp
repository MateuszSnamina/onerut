#ifndef ONERUT_PARSER_IDENTIFIER
#define ONERUT_PARSER_IDENTIFIER

#include<onerut_parser/compile_result_deref.hpp>

namespace onerut_parser {

    class AbstractCompileResultRef {//TODO holder->ref
    public:
        virtual CompileResultDeref get_compile_result() const = 0; // TODO zmienić na dereferenced compile result
        virtual ~AbstractCompileResultRef() = default;
    };

    class ConstDoubleHolder : public AbstractCompileResultRef {
    public:
        ConstDoubleHolder(double value);
        CompileResultDeref get_compile_result() const override;
        const double value;
    };

    class CompileResultConstRef : public AbstractCompileResultRef {
    public:
        CompileResultConstRef(std::u32string name, CompileResultDeref value);
        CompileResultDeref get_compile_result() const override;
        std::u32string get_name() const;
        //private: TODO
        const std::u32string name;
        const CompileResultDeref value;
    };

    class CompileResultNotConstRef : public AbstractCompileResultRef {
    public:
        CompileResultNotConstRef(std::u32string name, CompileResultDeref value);
        CompileResultDeref get_compile_result() const override;
        void set_compile_result(CompileResultDeref new_value);
        std::u32string get_name() const;
        //private: TODO
        const std::u32string name;
        CompileResultDeref value;
    };

}

#endif
