#pragma once

#include <headers/includes.h>

class MessageException : public std::exception {

	std::string mMessage;

public:

	MessageException();
	explicit MessageException(const std::string& message);

	const char * what() const noexcept override;
};