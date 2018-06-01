#ifndef PARSER_EXCEPTION_HPP
#define PARSER_EXCEPTION_HPP

#include <string>
#include <exception>

class ParserException : public std::exception {
	public:
		ParserException();
		ParserException(std::string const& error);
		ParserException(ParserException const& obj);
		~ParserException() noexcept = default;

		virtual const char* what() const noexcept;

		ParserException& operator=(ParserException const& obj);
	private:
		std::string _error;
};

#endif
