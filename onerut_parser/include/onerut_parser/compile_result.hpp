#ifndef ONERUT_PARSER_BUILD_RESULT
#define ONERUT_PARSER_BUILD_RESULT

#include<cassert>
#include<memory>
#include<variant>
#include<optional>
#include<any>
#include<stdexcept>

#include<onerut_parser/compile_result_error.hpp>
#include<onerut_parser/compile_result_deref.hpp>
#include<onerut_parser/identifier.hpp>


namespace onerut_parser {

    class CompileResult {
    public:
        // Construction:
        CompileResult() = default;
        CompileResult(const CompileResult&) = default; // TODO explicit??
        CompileResult(CompileResult&&) = default;
        CompileResult & operator=(const CompileResult&) = default;
        CompileResult & operator=(CompileResult&&) = default;
        static CompileResult from_reference(std::shared_ptr<AbstractCompileResultRef> reference);
        static CompileResult from_dereferenced_compile_result(CompileResultDeref dereferenced_compile_result);
        template<typename T> static CompileResult from_type();
        template<typename T> static CompileResult from_value(std::shared_ptr<T> value);
        static CompileResult from_compile_error(std::shared_ptr<CompileError> error);
        bool is_reference() const;
        std::optional<std::shared_ptr<AbstractCompileResultRef>> reference_or_empty() const;
        std::optional<CompileResultDeref> dereferenced_compile_result_or_empty() const;
        CompileResultDeref dereference() const;
        //TO DO _or_throw member functions.
    private:
        using VariantType = std::variant<
                std::shared_ptr<AbstractCompileResultRef>,
                CompileResultDeref>;
        VariantType _content;
        // We use the tag 'from_content' to mope up the overload issues:
        // DereferencedCompileResult(const VariantType) vs DereferencedCompileResult(const DereferencedCompileResult&)
        struct FromContentT;
        static const FromContentT from_content;
        CompileResult(const VariantType content, FromContentT);
    };

    struct CompileResult::FromContentT {
    };

    // *************************************************************************
    // ********   TEMPLATES IMPLEMENTATION   ***********************************
    // *************************************************************************

    template<typename T>
    CompileResult CompileResult::from_type() {
        CompileResultDeref dereferenced_compile_result = CompileResultDeref::from_type<T>();
        return from_dereferenced_compile_result(dereferenced_compile_result);
    }

    template<typename T>
    CompileResult CompileResult::from_value(std::shared_ptr<T> value) {
        CompileResultDeref dereferenced_compile_result = CompileResultDeref::from_value(value);
        return from_dereferenced_compile_result(dereferenced_compile_result);
    }
}
#endif
