#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <regex>

class Lexer {
	public:
		Lexer() = delete;
		Lexer(int argc, char* argv[]);
		Lexer(const Lexer& obj) = delete;
		~Lexer();
		
		const std::vector<std::vector<std::string>>& getTokens();

		Lexer& operator=(const Lexer& obj) = delete;
	private:
		std::vector<std::vector<std::string>> _tokens;
		std::string _errors;
		unsigned long numberOfLineWithError = 0;

		void printOutUsage();
		int isFileRegular(const char* path);
		void readFromFile(char *file);
		void readFromStandardInput();
		bool areTokensEmpty();
		void lineValidation(std::string input);
		void processingShortCommands(std::smatch match);
		void processingCommandsWithArguments(std::smatch match);
		void processingEmptyLinesAndComments();
};

#endif
