#ifndef ONERUT_PARSER_BUILD_RESULT_ERROR
#define ONERUT_PARSER_BUILD_RESULT_ERROR

#include<stdexcept>

namespace onerut_parser {

    class CompileError : public std::runtime_error {
    public:
        CompileError(const std::string& message);
    };

    class FunctionNotFoundError : public CompileError {
    public:
        FunctionNotFoundError(const std::string& function_name);
        const std::string function_name;
    };

    class IdentifierNotFoundError : public CompileError {
    public:
        IdentifierNotFoundError(const std::string& identifier_name);
        const std::string identifier_name;
    };

    class CompileArgumentsError : public CompileError {
    public:
        CompileArgumentsError();
    };

    class ArgumentMismatchError : public CompileError {
    public:
        ArgumentMismatchError();
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

}
#endif
