#include<onerut_parser/unicode_support.hpp>
#include<onerut_parser/build_result.hpp>

namespace onerut_parser {

    // *************************************************************************
    // ********************** ERRORS          **********************************
    // *************************************************************************

    BuildError::BuildError(const std::u32string& message) :
    std::runtime_error(unicode_to_utf8(message)) {
    }

    FunctionNotFoundError::FunctionNotFoundError(const std::u32string& function_name) :
    BuildError(U"FunctionNotFoundError! (Details: the function name = '" + function_name + U"'.)") {
    }

    IdentifierNotFoundError::IdentifierNotFoundError(const std::u32string& identifier_name) :
    BuildError(U"IdentifierNotFoundError! (Details: the identifier name = '" + identifier_name + U"'.)") {
    }

    BuildArgumentsError::BuildArgumentsError() :
    BuildError(U"BuildArgumentsError!") {
    }

    ArgumentMismatchError::ArgumentMismatchError() :
    BuildError(U"ArgumentMismatchError!") {
    }

    BuildNotImplementedError::BuildNotImplementedError() :
    BuildError(U"BuildNotImplementedError!") {
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
                throw std::runtime_error("BuildResult: Empty result type has no value.");
            }

            std::any operator()(const std::any& x) const {
                return x;
            }

            std::any operator()(std::shared_ptr<BuildError> error) const {
                assert(error);
                throw *error;
            }

        };

    }

    // *************************************************************************
    // ********************** BUILDER RESULTS **********************************
    // *************************************************************************    

    BuildResult::BuildResult(const BuildResult::VariantType content) :
    _content(content) {
    }

    BuildResult
    BuildResult::from_build_error(std::shared_ptr<BuildError> error) {
        assert(error);
        BuildResult::VariantType content{
            std::in_place_type<std::shared_ptr < BuildError>>,
            error};
        return BuildResult(content);
    }

    std::optional<std::any>
    BuildResult::value_or_empty() const {
        const ContentOrEmptyVisitor<std::any> value_or_empty_visitor;
        return std::visit(value_or_empty_visitor, _content);
    }

    std::optional<std::shared_ptr < BuildError >>
    BuildResult::build_error_or_empty() const {
        const ContentOrEmptyVisitor<std::shared_ptr < BuildError>> build_error_or_empty_visitor;
        return std::visit(build_error_or_empty_visitor, _content);
    }

    std::any
    BuildResult::value_or_throw() const {
        const ValueOrThrowVisitor value_or_throw_visitor;
        return std::visit(value_or_throw_visitor, _content);
    }

    bool
    BuildResult::is_empty() const {
        const IsContentVisitor<std::monostate> is_empty_visitor;
        return std::visit(is_empty_visitor, _content);
    }

    bool
    BuildResult::is_either_value_or_type() const {
        const IsContentVisitor<std::any> is_either_value_or_type_visitor;
        return std::visit(is_either_value_or_type_visitor, _content);
    }

    bool
    BuildResult::is_error() const {
        const IsContentVisitor<std::shared_ptr < BuildError>> is_build_error_visitor;
        return std::visit(is_build_error_visitor, _content);
    }

}