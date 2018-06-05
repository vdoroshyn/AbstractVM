#include "ParserException.hpp"

ParserException::ParserException() {
}

ParserException::ParserException(const std::string& error): _error(error) {
}

ParserException::ParserException(const ParserException& obj) {
	*this = obj;
}

ParserException& ParserException::operator=(const ParserException& obj) {
	if (this != &obj) {
		this->_error = obj._error;
	}
	return *this;
}

const char* ParserException::what() const noexcept {
	return this->_error.c_str();
}
