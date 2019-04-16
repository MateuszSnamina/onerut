#ifndef ONERUT_PARSER_ASSET_ERROR
#define ONERUT_PARSER_ASSET_ERROR

#include<stdexcept>

namespace onerut_parser_exec {

    class CompileError : public std::runtime_error {
    public:
        CompileError(const std::string& message);
    };

    class FunctionNotFoundError : public CompileError {
    public:
        FunctionNotFoundError(const std::string& function_name);
        const std::string function_name;
    };

    class CompileArgumentsError : public CompileError {
    public:
        CompileArgumentsError();
    };

    class ArgumentMismatchError : public CompileError {
    public:
        ArgumentMismatchError();
    };

    class ArgumentDomainError : public CompileError {
    public:
        ArgumentDomainError(const std::string& message);
    };

    class WrongNumberOfArgumentsError : public CompileError {
    public:
        WrongNumberOfArgumentsError();
    };

    class IllegalAssignAttemptToRValueError : public CompileError {
    public:
        IllegalAssignAttemptToRValueError();
    };

    class IllegalAssignAttemptToConstReferenceError : public CompileError {
    public:
        IllegalAssignAttemptToConstReferenceError();
    };

    class IllegalAssignAttemptToSetReferenceError : public CompileError {
    public:
        IllegalAssignAttemptToSetReferenceError();
    };

    class IllegalSecondAssignError : public CompileError {
    public:
        IllegalSecondAssignError();
    };

    class CompilerNotImplementedError : public CompileError {
    public:
        CompilerNotImplementedError();
    };

}
#endif
