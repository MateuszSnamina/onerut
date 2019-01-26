#ifndef ONERUT_PARSER_BUILDER
#define ONERUT_PARSER_BUILDER

#include<memory>
#include<variant>
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
    virtual std::any value() const = 0;
    //virtual std::optional<std::any> value() const = 0;
    virtual std::shared_ptr<ArgumentMismatchError> argument_mismatch_error() = 0;
    virtual std::shared_ptr<BuildError> build_error() = 0;
    virtual bool was_error() const;
    virtual bool was_argument_mismatch_error() const = 0;
    virtual bool was_build_error() const = 0;
};

template<class T>
class TypedBuildResult : public BuildResult {
public:
    virtual std::shared_ptr<T> value_typed() const = 0;
    virtual std::any value() const override;
    virtual bool was_argument_mismatch_error() const = 0;
    virtual bool was_build_error() const = 0;
};

template<class T>
class TypedBuildResultVariantImpl : public TypedBuildResult<T> {
public:
    virtual std::shared_ptr<T> value_typed() const override;
    virtual ArgumentMismatchError argument_mismatch_error() = 0;
    virtual BuildError build_error() = 0;
    virtual bool was_argument_mismatch_error() const override;
    virtual bool was_build_error() const override;
    const std::variant<
    std::shared_ptr<T>,
    std::shared_ptr<ArgumentMismatchError>,
    std::shared_ptr<BuildError>
    > content;
};

// -----------------------------------------------------------------------------

bool BuildResult::was_error() const {
    return was_argument_mismatch_error() || was_build_error();
}

template<class T>
std::any TypedBuildResult<T>::value() const {
    return value_typed();
}

// *****************************************************************************
// ********************** ERRORS          **************************************
// *****************************************************************************

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


#endif
