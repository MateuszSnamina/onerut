#include<onerut_parser/common_visitors.hpp>
#include<onerut_parser/compile_result.hpp>

namespace onerut_parser {

    // *************************************************************************
    // ********************** HELPER FUNCTIONS   *******************************
    // *************************************************************************

    namespace {

        struct DereferenceVisitor {
            CompileResultDeref operator()(const std::shared_ptr < AbstractCompileResultRef>& reference) const;
            CompileResultDeref operator()(const CompileResultDeref& results) const;
        };

        CompileResultDeref
        DereferenceVisitor::operator()(const std::shared_ptr < AbstractCompileResultRef>& reference) const {
            return reference->get_compile_result_deref();
        }

        CompileResultDeref
        DereferenceVisitor::operator()(const CompileResultDeref& results) const {
            return results;
        }

    }

    // *************************************************************************
    // ********************** COMPILE RESULT ***********************************
    // *************************************************************************    

    CompileResult::CompileResult(const VariantType content, FromContentT) :
    _content(content) {
    }

    CompileResult CompileResult::from_reference(std::shared_ptr<AbstractCompileResultRef> reference) {
        CompileResult::VariantType content{
            std::in_place_type<std::shared_ptr < AbstractCompileResultRef>>,
            reference};
        return CompileResult(content, from_content);
    }

    CompileResult
    CompileResult::from_dereferenced_compile_result(CompileResultDeref dereferenced_compile_result) {
        CompileResult::VariantType content{
            std::in_place_type<CompileResultDeref>,
            dereferenced_compile_result};
        return CompileResult(content, from_content);
    }

    CompileResult
    CompileResult::from_compile_error(std::shared_ptr<CompileError> error) {
        CompileResultDeref dereferenced_compile_result = CompileResultDeref::from_compile_error(error);
        return from_dereferenced_compile_result(dereferenced_compile_result);
    }

    bool
    CompileResult::is_reference() const {
        const IsContentVisitor<std::shared_ptr < AbstractCompileResultRef>> is_empty_visitor;
        return std::visit(is_empty_visitor, _content);
    }

    std::optional<std::shared_ptr<AbstractCompileResultRef>>
    CompileResult::reference_or_empty() const {
        const ContentOrEmptyVisitor<std::shared_ptr < AbstractCompileResultRef>> reference_or_empty_visitor;
        return std::visit(reference_or_empty_visitor, _content);
    }

    std::optional<CompileResultDeref>
    CompileResult::dereferenced_compile_result_or_empty() const {
        const ContentOrEmptyVisitor<CompileResultDeref> dereferenced_compile_result_or_empty_visitor;
        return std::visit(dereferenced_compile_result_or_empty_visitor, _content);
    }

    CompileResultDeref
    CompileResult::dereference() const {
        const DereferenceVisitor dereference_visitor;
        return std::visit(dereference_visitor, _content);

    }

}