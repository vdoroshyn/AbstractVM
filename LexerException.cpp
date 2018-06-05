#include "LexerException.hpp"

LexerException::LexerException() {
}

LexerException::LexerException(const std::string& error): _error(error) {
}

LexerException::LexerException(const LexerException& obj) {
	*this = obj;
}

LexerException& LexerException::operator=(const LexerException& obj) {
	if (this != &obj) {
		this->_error = obj._error;
	}
	return *this;
}

const char* LexerException::what() const noexcept {
	return this->_error.c_str();
}
