#include "ParserException.hpp"

ParserException::ParserException() {
}

ParserException::ParserException(std::string const& error): _error(error) {
}

ParserException::ParserException(ParserException const& obj) {
	*this = obj;
}

ParserException& ParserException::operator=(ParserException const& obj) {
	if (this != &obj) {
		this->_error = obj._error;
	}
	return *this;
}

const char* ParserException::what() const noexcept {
	return this->_error.c_str();
}
