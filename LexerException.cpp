#include "LexerException.hpp"

LexerException::LexerException() {
}

LexerException::LexerException(std::string const& error): _error(error) {
}

LexerException::LexerException(LexerException const& obj) {
	*this = obj;
}

LexerException& LexerException::operator=(LexerException const& obj) {
	if (this != &obj) {
		this->_error = obj._error;
	}
	return *this;
}

const char* LexerException::what() const noexcept {
	return this->_error.c_str();
}
