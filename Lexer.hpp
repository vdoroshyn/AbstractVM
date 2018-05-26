#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <vector>
#include <regex>

class Lexer {
	public:
		Lexer();
		Lexer(int argc, char* argv[]);
		Lexer(Lexer const& obj);
		~Lexer();

		void readFromFile(char *file);
		void readFromStandardInput();
		void lineValidation(std::string input);
		void processingShortCommands(std::smatch match);
		void processingCommandsWithArguments(std::smatch match);
		void processingEmptyLinesAndComments();
		
		const std::vector<std::vector<std::string>>& getTokens();

		Lexer& operator=(Lexer const& obj);
	private:
		std::vector<std::vector<std::string>> tokens;
		std::string errors;
};

#endif
