#ifndef MINECRAFT_MESSAGEEXCEPTION_H
#define MINECRAFT_MESSAGEEXCEPTION_H

#include <headers/includes.h>

class MessageException : public std::exception {

    std::string mMessage;

public:

    MessageException();
    MessageException(const std::string& message);

    const char * what() const noexcept override;
};

#endif //MINECRAFT_MESSAGEEXCEPTION_H