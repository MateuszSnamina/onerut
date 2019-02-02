#ifndef ONERUT_PARSER_IDENTIFIER
#define ONERUT_PARSER_IDENTIFIER

#include<onerut_parser/compile_result.hpp>

namespace onerut_parser {

    class AbstractCompileResultHolder {//TODO holder->ref
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

    class CompileResultConstRef : public AbstractCompileResultHolder {
    public:
        CompileResultConstRef(std::u32string name, CompileResult value);
        CompileResult get_compile_result() const override;
        std::u32string get_name() const;
        //private: TODO
        const std::u32string name;
        const CompileResult value;
    };

    class CompileResultRef : public AbstractCompileResultHolder {
    public:
        CompileResultRef(std::u32string name, CompileResult value);
        CompileResult get_compile_result() const override;
        void set_compile_result(CompileResult new_value);
        std::u32string get_name() const;
        //private: TODO
        const std::u32string name;
        CompileResult value;
    };

}

#endif
