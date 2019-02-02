#include<onerut_parser/unicode_support.hpp>
#include<onerut_parser/compile_result.hpp>

namespace onerut_parser {

    // *************************************************************************
    // ********************** ERRORS          **********************************
    // *************************************************************************

    CompileError::CompileError(const std::u32string& message) :
    std::runtime_error(unicode_to_utf8(message)) {
    }

    FunctionNotFoundError::FunctionNotFoundError(const std::u32string& function_name) :
    CompileError(U"FunctionNotFoundError! (Details: the function name = '" + function_name + U"'.)"),
    function_name(function_name) {
    }

    IdentifierNotFoundError::IdentifierNotFoundError(const std::u32string& identifier_name) :
    CompileError(U"Identifier not found error! (Details: the identifier name = '" + identifier_name + U"'.)"),
    identifier_name(identifier_name) {
    }

    CompileArgumentsError::CompileArgumentsError() :
    CompileError(U"Compile arguments error!") {
    }

    ArgumentMismatchError::ArgumentMismatchError() :
    CompileError(U"Argument mismatch error!") {
    }

    IllegalAssignAttemptToRValueError::IllegalAssignAttemptToRValueError() :
    CompileError(U"Illegal assign attempt to r-value error!") {
    }

    IllegalAssignAttemptToConstReferenceError::IllegalAssignAttemptToConstReferenceError() :
    CompileError(U"Illegal assign attempt to const reference error!") {
    }

    IllegalAssignAttemptToReferenceError::IllegalAssignAttemptToReferenceError() :
    CompileError(U"Illegal assign attempt to reference error!") {
    }

    CompilerNotImplementedError::CompilerNotImplementedError() :
    CompileError(U"Compiler not implemented error!") {
    }

    // *************************************************************************
    // ********************** HELPER FUNCTIONS   *******************************
    // *************************************************************************

    namespace {

        // -------------------------------------------------------------------------

        template<typename VariantContentType>
        struct ContentOrEmptyVisitor {
            using ResultType = std::optional<VariantContentType>;

            ResultType operator()(const VariantContentType& x) const {
                return x;
            }

            template<typename U>
            ResultType operator()(const U& x) const {
                return ResultType();
            }

        };

        // -------------------------------------------------------------------------

        template<typename VariantContentType>
        struct IsContentVisitor {

            bool operator()(const VariantContentType& x) const {
                return true;
            }

            template<typename U>
            bool operator()(const U& x) const {
                return false;
            }

        };

        // -------------------------------------------------------------------------

        struct ValueOrThrowVisitor {

            std::any operator()(const std::monostate&) const {
                throw std::runtime_error("CompileResult: Empty result type has no value.");
            }

            std::any operator()(const std::any& x) const {
                return x;
            }

            std::any operator()(std::shared_ptr<CompileError> error) const {
                assert(error);
                throw *error;
            }

        };

    }

    // *************************************************************************
    // ********************** COMPILE RESULT ***********************************
    // *************************************************************************    

    CompileResult::CompileResult(const CompileResult::VariantType content, FromContentT) :
    _content(content) {
    }

    CompileResult
    CompileResult::from_compile_error(std::shared_ptr<CompileError> error) {
        assert(error);
        CompileResult::VariantType content{
            std::in_place_type<std::shared_ptr < CompileError>>,
            error};
        return CompileResult(content, from_content);
    }

    std::optional<std::any>
    CompileResult::value_or_empty() const {
        const ContentOrEmptyVisitor<std::any> value_or_empty_visitor;
        return std::visit(value_or_empty_visitor, _content);
    }

    std::optional<std::shared_ptr < CompileError >>
    CompileResult::compile_error_or_empty() const {
        const ContentOrEmptyVisitor<std::shared_ptr < CompileError>> compile_error_or_empty_visitor;
        return std::visit(compile_error_or_empty_visitor, _content);
    }

    std::any
    CompileResult::value_or_throw() const {
        const ValueOrThrowVisitor value_or_throw_visitor;
        return std::visit(value_or_throw_visitor, _content);
    }

    bool
    CompileResult::is_empty() const {
        const IsContentVisitor<std::monostate> is_empty_visitor;
        return std::visit(is_empty_visitor, _content);
    }

    bool
    CompileResult::is_either_value_or_type() const {
        const IsContentVisitor<std::any> is_either_value_or_type_visitor;
        return std::visit(is_either_value_or_type_visitor, _content);
    }

    bool
    CompileResult::is_compile_error() const {
        const IsContentVisitor<std::shared_ptr < CompileError>> is_compile_error_visitor;
        return std::visit(is_compile_error_visitor, _content);
    }

}