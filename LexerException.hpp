#ifndef LEXER_EXCEPTION_HPP
#define LEXER_EXCEPTION_HPP

#include <iostream>
#include <exception>

class LexerException : public std::exception {
	public:
		LexerException();
		LexerException(std::string const& error);
		LexerException(LexerException const& obj) = delete;
		~LexerException() noexcept = default;

		virtual const char* what() const noexcept;



		LexerException& operator=(LexerException const& obj) = delete;
	private:
		const std::string _error;
};

#endif
