#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>

class Lexer {
	public:
		Lexer();
		Lexer(int argc, char* argv[]);
		Lexer(Lexer const& obj);
		~Lexer();

		void readFromFile(char *file);
		void readFromStandardInput();
		void lineValidation(std::string input);

		Lexer& operator=(Lexer const& obj);
};

#endif
