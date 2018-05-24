#ifndef LEXER_EXCEPTION_HPP
#define LEXER_EXCEPTION_HPP

#include <iostream>
#include <exception>

class LexerException : public std::exception {
	public:
		LexerException();
		LexerException(std::string const& error);
		LexerException(LexerException const& obj);
		~LexerException() noexcept = default;

		virtual const char* what() const noexcept;

		LexerException& operator=(LexerException const& obj);
	private:
		std::string _error;
};

#endif
