#include<string_utils/unicode_support.hpp>
#include<onerut_parser/compile_result.hpp>

namespace onerut_parser {

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
    
    WrongNumberOfArgumentsError::WrongNumberOfArgumentsError() :
    CompileError(U"Wrong number of arguments error!") {
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

    IllegalSecondAssignError::IllegalSecondAssignError() :
    CompileError(U"Illegal second assign error!") {
    }

    CompilerNotImplementedError::CompilerNotImplementedError() :
    CompileError(U"Compiler not implemented error!") {
    }

}