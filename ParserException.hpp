#ifndef PARSER_EXCEPTION_HPP
#define PARSER_EXCEPTION_HPP

#include <string>
#include <exception>

class ParserException : public std::exception {
	public:
		ParserException();
		ParserException(const std::string& error);
		ParserException(const ParserException& obj);
		~ParserException() noexcept = default;

		virtual const char* what() const noexcept;

		ParserException& operator=(const ParserException& obj);
	private:
		std::string _error;
};

#endif
