#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <vector>

class Lexer {
	public:
		std::vector<std::vector<std::string>> tokens;

		Lexer();
		Lexer(int argc, char* argv[]);
		Lexer(Lexer const& obj);
		~Lexer();

		void readFromFile(char *file);
		void readFromStandardInput();
		void lineValidation(std::string input);

		Lexer& operator=(Lexer const& obj);
	private:
		std::string errors;
};

#endif
