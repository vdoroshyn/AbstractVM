#ifndef LEXER_EXCEPTION_HPP
#define LEXER_EXCEPTION_HPP

#include <string>
#include <exception>

class LexerException : public std::exception {
	public:
		LexerException();
		LexerException(const std::string& error);
		LexerException(const LexerException& obj);
		~LexerException() noexcept = default;

		virtual const char* what() const noexcept;

		LexerException& operator=(const LexerException& obj);
	private:
		std::string _error;
};

#endif
