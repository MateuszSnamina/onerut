#ifndef ONERUT_PARSER_IDENTIFIER
#define ONERUT_PARSER_IDENTIFIER

#include<onerut_parser/compile_result.hpp>

namespace onerut_parser {

    class AbstractCompileResultRef {//TODO holder->ref
    public:
        virtual DereferencedCompileResult get_compile_result() const = 0; // TODO zmienić na dereferenced compile result
        virtual ~AbstractCompileResultRef() = default;
    };

    class ConstDoubleHolder : public AbstractCompileResultRef {
    public:
        ConstDoubleHolder(double value);
        DereferencedCompileResult get_compile_result() const override;
        const double value;
    };

    class CompileResultConstRef : public AbstractCompileResultRef {
    public:
        CompileResultConstRef(std::u32string name, DereferencedCompileResult value);
        DereferencedCompileResult get_compile_result() const override;
        std::u32string get_name() const;
        //private: TODO
        const std::u32string name;
        const DereferencedCompileResult value;
    };

    class CompileResultNotConstRef : public AbstractCompileResultRef {
    public:
        CompileResultNotConstRef(std::u32string name, DereferencedCompileResult value);
        DereferencedCompileResult get_compile_result() const override;
        void set_compile_result(DereferencedCompileResult new_value);
        std::u32string get_name() const;
        //private: TODO
        const std::u32string name;
        DereferencedCompileResult value;
    };

}

#endif
