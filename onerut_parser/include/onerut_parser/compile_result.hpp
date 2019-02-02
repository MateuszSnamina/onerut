#ifndef ONERUT_PARSER_BUILD_RESULT
#define ONERUT_PARSER_BUILD_RESULT

#include<cassert>
#include<memory>
#include<variant>
#include<optional>
#include<any>
#include<stdexcept>

namespace onerut_parser {

    // *************************************************************************
    // ********************** ERRORS          **********************************
    // *************************************************************************

    class CompileError : public std::runtime_error {
    public:
        CompileError(const std::u32string& message);
    };

    class FunctionNotFoundError : public CompileError {
    public:
        FunctionNotFoundError(const std::u32string& function_name);
        const std::u32string function_name;
    };

    class IdentifierNotFoundError : public CompileError {
    public:
        IdentifierNotFoundError(const std::u32string& identifier_name);
        const std::u32string identifier_name;
    };

    class CompileArgumentsError : public CompileError {
    public:
        CompileArgumentsError();
    };

    class ArgumentMismatchError : public CompileError {
    public:
        ArgumentMismatchError();
    };

    class IllegalAssignAttemptToRValueError : public CompileError {
    public:
        IllegalAssignAttemptToRValueError();
    };

    class IllegalAssignAttemptToConstReferenceError : public CompileError {
    public:
        IllegalAssignAttemptToConstReferenceError();
    };

    class IllegalAssignAttemptToReferenceError : public CompileError {
    public:
        IllegalAssignAttemptToReferenceError();
    };

    class IllegalSecondAssignError : public CompileError {
    public:
        IllegalSecondAssignError();
    };    
    
    class CompilerNotImplementedError : public CompileError {
    public:
        CompilerNotImplementedError();
    };

    // *************************************************************************
    // ********************** BUILDER RESULTS **********************************
    // *************************************************************************

    class CompileResult {
    public:
        // Construction:
        CompileResult() = default;
        CompileResult(const CompileResult&) = default; // TODO explicit??
        CompileResult(CompileResult&&) = default;
        CompileResult & operator=(const CompileResult&) = default;
        CompileResult & operator=(CompileResult&&) = default;
        template<typename T> static CompileResult from_type();
        template<typename T> static CompileResult from_value(std::shared_ptr<T> value);
        static CompileResult from_compile_error(std::shared_ptr<CompileError> error);
        // Accessors and predicates:
        template<typename T> bool is_given_type() const;
        std::optional<std::any> value_or_empty() const;
        std::optional<std::shared_ptr<CompileError>> compile_error_or_empty() const;
        std::any value_or_throw() const;
        template<typename T> std::optional<std::shared_ptr<T>> typed_value_or_empty() const;
        template<typename T> std::shared_ptr<T> typed_value_or_throw() const;
        bool is_empty() const;
        bool is_either_value_or_type() const;
        bool is_compile_error() const;
    private:
        using VariantType = std::variant<
                std::monostate,
                std::shared_ptr<CompileError>,
                std::any>;
        VariantType _content;
        // We use the tag 'from_content' to mope up the overload issues:
        // CompileResult(const VariantType) vs CompileResult(const CompileResult&)
        struct FromContentT;
        static const FromContentT from_content;
        CompileResult(const VariantType content, FromContentT);
    };

    struct CompileResult::FromContentT {
    };

    // *************************************************************************
    // ********   TEMPLATES IMPLEMENTATION -- HELPER FUNCTIONS  ****************
    // *************************************************************************

    namespace {

        template<typename T>
        struct IsGivenTypeVisitor {
            using AnyContentType = std::shared_ptr<T>;
            using ResultType = bool;

            ResultType operator()(const std::any& x) const {
                try {
                    std::any_cast<AnyContentType>(x);
                } catch (std::bad_any_cast &) {
                    return false;
                }
                return true;
            }

            template<typename U>
            ResultType operator()(const U& x) const {
                return false;
            }
        };

        template<typename T>
        struct TypedValueOrThrowVisitor {
            using ResultType = std::shared_ptr<T>;

            ResultType operator()(const std::monostate&) const {
                throw std::runtime_error("BuildResult: Empty result type has no value.");
            }

            ResultType operator()(const std::any& x) const {
                try {
                    return std::any_cast<ResultType>(x);
                } catch (std::bad_any_cast &) {
                    throw std::runtime_error("BuildResult: Result type mismatch.");
                }
            }

            ResultType operator()(std::shared_ptr<CompileError> error) const {
                assert(error);
                throw *error;
            }

        };

        template<typename T>
        struct TypedValueOrEmptyVisitor {
            using AnyContentType = std::shared_ptr<T>;
            using ResultType = std::optional<AnyContentType>;

            ResultType operator()(const std::any& x) const {
                try {
                    return std::any_cast<AnyContentType>(x);
                } catch (std::bad_any_cast &) {
                    return ResultType();
                }
            }

            template<typename U>
            ResultType operator()(const U& x) const {
                return ResultType();
            }

        };

    }

    // *************************************************************************
    // ********   TEMPLATES IMPLEMENTATION   ***********************************
    // *************************************************************************

    template<typename T>
    CompileResult CompileResult::from_type() {
        std::shared_ptr<T> value;
        CompileResult::VariantType content{
            std::in_place_type<std::any>,
            value};
        return CompileResult(content, from_content);
    }

    template<typename T>
    CompileResult CompileResult::from_value(std::shared_ptr<T> value) {
        assert(value);
        CompileResult::VariantType content{
            std::in_place_type<std::any>,
            value};
        return CompileResult(content, from_content);
    }

    template<typename T>
    bool CompileResult::is_given_type() const {
        const IsGivenTypeVisitor<T> is_given_type_visitor;
        return std::visit(is_given_type_visitor, _content);
    }

    template<typename T>
    std::optional<std::shared_ptr<T>> CompileResult::typed_value_or_empty() const {
        const TypedValueOrEmptyVisitor<T> type_value_or_empty_visitor;
        return std::visit(type_value_or_empty_visitor, _content);
    }

    template<typename T>
    std::shared_ptr<T> CompileResult::typed_value_or_throw() const {
        const TypedValueOrThrowVisitor<T> type_value_or_throw_visitor;
        return std::visit(type_value_or_throw_visitor, _content);
    }

}
#endif
