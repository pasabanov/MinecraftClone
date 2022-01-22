#include "MessageException.h"



MessageException::MessageException() : std::exception() {}



MessageException::MessageException(const std::string& message) : std::exception(), mMessage(message) {}



const char* MessageException::what() const noexcept {
    return mMessage.c_str();
}