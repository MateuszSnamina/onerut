#include<onerut_parser_exec/asset.hpp>

namespace onerut_parser_exec {

    CompileError::CompileError(const std::string& message) :
    std::runtime_error(message) {
    }

    FunctionNotFoundError::FunctionNotFoundError(const std::string& function_name) :
    CompileError("FunctionNotFoundError! (Details: the function name = '" + function_name + "'.)"),
    function_name(function_name) {
    }

    CompileArgumentsError::CompileArgumentsError() :
    CompileError("Compile arguments error!") {
    }

    ArgumentMismatchError::ArgumentMismatchError() :
    CompileError("Argument mismatch error!") {
    }

    ArgumentDomainError::ArgumentDomainError(const std::string& message) :
    CompileError("Argument domain error!" + (message.empty() ? "" : " " + message)) {
    }

    WrongNumberOfArgumentsError::WrongNumberOfArgumentsError() :
    CompileError("Wrong number of arguments error!") {
    }

    IllegalAssignAttemptToRValueError::IllegalAssignAttemptToRValueError() :
    CompileError("Illegal assign attempt to r-value error!") {
    }

    IllegalAssignAttemptToConstReferenceError::IllegalAssignAttemptToConstReferenceError() :
    CompileError("Illegal assign attempt to const reference error!") {
    }

    IllegalAssignAttemptToSetReferenceError::IllegalAssignAttemptToSetReferenceError() :
    CompileError("Illegal assign attempt to set reference error!") {
    }

    IllegalSecondAssignError::IllegalSecondAssignError() :
    CompileError("Illegal second assign error!") {
    }

    CompilerNotImplementedError::CompilerNotImplementedError() :
    CompileError("Compiler not implemented error!") {
    }

}