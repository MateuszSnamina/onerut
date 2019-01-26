#ifndef ONERUT_PARSER_BUILDER
#define ONERUT_PARSER_BUILDER

#include<cassert>
#include<memory>
#include<variant>
#include<optional>
#include<any>
#include<stdexcept>

#include<onerut_scalar/scalar.hpp>

// *****************************************************************************
// ********************** ERRORS          **************************************
// *****************************************************************************

class ArgumentMismatchError : public std::runtime_error {
    ArgumentMismatchError(const std::string& message);
};

class BuildError : public std::runtime_error {
    BuildError(const std::string& message);
};



// *****************************************************************************
// ********************** BUILDER RESULTS **************************************
// *****************************************************************************

class BuildResult {
public:
    BuildResult() = default;
    template<typename T>
    BuildResult from_type();
    template<typename T>
    BuildResult from_value(std::shared_ptr<T> value);
    BuildResult from_argument_mismatch_error(std::shared_ptr<ArgumentMismatchError> value);
    BuildResult from_build_error(std::shared_ptr<BuildError> value);

    template<typename T>
    bool is_given_type() const;

    std::optional<std::any> value_or_empty() const;
    std::optional<std::shared_ptr<ArgumentMismatchError>> argument_mismatch_error_or_empty() const;
    std::optional<std::shared_ptr<BuildError>> build_error_or_empty() const;
    std::any value_or_throw() const;

    template<typename T>
    std::optional<std::shared_ptr<T>> typed_value_or_empty() const;
    template<typename T>
    std::shared_ptr<T> typed_value_or_throw() const;

    bool is_empty() const;
    bool is_argument_mismatch_error() const;
    bool is_build_error() const;
    bool is_error() const;


private:
    using ContentType = std::variant<
            std::monostate,
            std::any,
            std::shared_ptr<ArgumentMismatchError>,
            std::shared_ptr<BuildError>
            >;
    const ContentType _content;
    explicit BuildResult(const ContentType content);
};


// *****************************************************************************
// ********   IMPLEMENTACJA  ***************************************************
// *****************************************************************************

namespace {

    template<typename T>
    struct IsGivenTypeVisitor {
        using AnyContentType = std::shared_ptr<T>;
        using ResultType = bool;

        ResultType operator()(const std::any& x) const {
            try {
                std::any_cast<AnyContentType>(x);
                return true;
            } catch (std::bad_any_cast &) {
                return false;
            }
        }

        template<typename U>
        ResultType operator()(const U& x) const {
            return false;
        }
    };

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

    struct ValueOrThrowVisitor {

        std::any operator()(const std::monostate&) const {
            throw std::runtime_error("BuildResult: Empty result type has no value.");
        }

        std::any operator()(const std::any& x) const {
            return x;
        }

        std::any operator()(std::shared_ptr<ArgumentMismatchError> error) const {
            assert(error);
            throw *error;
        }

        std::any operator()(std::shared_ptr<BuildError> error) const {
            assert(error);
            throw *error;
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
                ;
            }
        }

        ResultType operator()(std::shared_ptr<ArgumentMismatchError> error) const {
            assert(error);
            throw *error;
        }

        ResultType operator()(std::shared_ptr<BuildError> error) const {
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
                throw;
            }
        }

        template<typename U>
        ResultType operator()(const U& x) const {
            return ResultType();
        }

    };

}

template<typename T>
BuildResult BuildResult::from_type() {
    std::shared_ptr<T> value = std::make_shared<T>(nullptr);
    BuildResult::ContentType content{std::in_place_type<std::any>, value};
    return BuildResult(content);
}

template<typename T>
BuildResult BuildResult::from_value(std::shared_ptr<T> value) {
    assert(value);
    BuildResult::ContentType content{
        std::in_place_type<std::any>, value};
    return BuildResult(content);
}

BuildResult BuildResult::from_argument_mismatch_error(std::shared_ptr<ArgumentMismatchError> error) {
    assert(error);
    BuildResult::ContentType content{std::in_place_type<std::shared_ptr < ArgumentMismatchError>>, error};
    return BuildResult(content);
}

BuildResult BuildResult::from_build_error(std::shared_ptr<BuildError> error) {
    assert(error);
    BuildResult::ContentType content{std::in_place_type<std::shared_ptr < BuildError>>, error};
    return BuildResult(content);
}

template<typename T>
bool BuildResult::is_given_type() const {
    const IsGivenTypeVisitor<T> is_given_type_visitor;
    return std::visit(is_given_type_visitor, _content);
}

std::optional<std::any> BuildResult::value_or_empty() const {
    const ContentOrEmptyVisitor<std::any> value_or_empty_visitor;
    return std::visit(value_or_empty_visitor, _content);
}

std::optional<std::shared_ptr<ArgumentMismatchError>> BuildResult::argument_mismatch_error_or_empty() const {
    const ContentOrEmptyVisitor<std::shared_ptr < ArgumentMismatchError>> argument_mismatch_error_or_empty_visitor;
    return std::visit(argument_mismatch_error_or_empty_visitor, _content);
}

std::optional<std::shared_ptr<BuildError>> BuildResult::build_error_or_empty() const {
    const ContentOrEmptyVisitor<std::shared_ptr < BuildError>> build_error_or_empty_visitor;
    return std::visit(build_error_or_empty_visitor, _content);
}

std::any BuildResult::value_or_throw() const {
    const ValueOrThrowVisitor value_or_throw_visitor;
    return std::visit(value_or_throw_visitor, _content);
}

template<typename T>
std::optional<std::shared_ptr<T>> BuildResult::typed_value_or_empty() const {
    const TypedValueOrEmptyVisitor<T> type_value_or_empty_visitor;
    return std::visit(type_value_or_empty_visitor, _content);
}

template<typename T>
std::shared_ptr<T> BuildResult::typed_value_or_throw() const {
    const TypedValueOrThrowVisitor<T> type_value_or_throw_visitor;
    return std::visit(type_value_or_throw_visitor, _content);
}

bool BuildResult::is_empty() const {
    const IsContentVisitor<std::monostate> is_empty_visitor;
    return std::visit(is_empty_visitor, _content);
}

bool BuildResult::is_argument_mismatch_error() const {
    const IsContentVisitor<std::shared_ptr < ArgumentMismatchError>> is_argument_mismatch_error_visitor;
    return std::visit(is_argument_mismatch_error_visitor, _content);
}

bool BuildResult::is_build_error() const {
    const IsContentVisitor<std::shared_ptr < BuildError>> is_build_error_visitor;
    return std::visit(is_build_error_visitor, _content);
}

bool BuildResult::is_error() const {
    return is_argument_mismatch_error() || is_build_error();
}

// *****************************************************************************
// ********************** BUILDERS        **************************************
// *****************************************************************************

/*
class Builder {
public:
    virtual BuildResult run() const = 0;
    virtual BuildResult dry_run() const = 0;
};

template<class T>
class TypedBuilder : public Builder {
public:
    BuildResult run() const override;
    BuildResult dry_run() const override;
    TypedBuildResult<T> run_typed() const;
    TypedBuildResult<T> dry_run_typed() const;
};

BuildResult TypedBuilder::run() {

}

BuildResult TypedBuilder::dry_run() {

}
 */

#endif
