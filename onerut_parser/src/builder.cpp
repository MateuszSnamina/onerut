#include<onerut_parser/builder.hpp>

ArgumentMismatchError::ArgumentMismatchError(const std::string& message) :
std::runtime_error(message) {
}

BuildError::BuildError(const std::string& message) :
std::runtime_error(message) {
}
