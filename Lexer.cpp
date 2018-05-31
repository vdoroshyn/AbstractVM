#include "Lexer.hpp"
#include "LexerException.hpp"
#include <iostream>
#include <fstream>
#include <regex>

Lexer::Lexer(int argc, char* argv[]) {
	if (argc == 1) {
		/*
		**read stuff from the standard input
		**end at user's input == ";;"
		*/
		this->readFromStandardInput();
	} else if (argc == 2) {
		/*
		**An Easter Egg for perverts in UNIT Factory
		*/
		std::string argument = std::string(argv[1]);
		if (argument == "/dev/zero" || argument == "/dev/null") {
			throw LexerException("Eric Exception: Congratulations! You are trying to check veeeeeery perverted cases!");
		}
		/*
		**read stuff from file
		**end at EOF
		*/
		this->readFromFile(argv[1]);
	} else {
		throw LexerException("There are too many arguments");
	}
}

Lexer::~Lexer() {
}

void Lexer::readFromFile(char* file) {
	std::ifstream ifstr(file);
	if (!ifstr.is_open()) {
		throw LexerException("The stream is not opened");
	}

	std::string input;

	while (std::getline(ifstr, input)) {
		this->lineValidation(input);
	}
	if (!this->_errors.empty()) {
		throw LexerException(this->_errors);
	}
	/*
	**Checking whether the user entered at least something
	*/
	if (areTokensEmpty()) {
		this->_errors += "You should have entered at least one command\n";
		throw LexerException(this->_errors);
	}
}

void Lexer::readFromStandardInput() {	
	std::string input;

	while (std::getline(std::cin, input) && input != ";;") {
		this->lineValidation(input);
	}
	// std::cout << "output number of lines with tokens: " << this->_tokens.size() << std::endl;
	// for (auto& line : this->_tokens) {
	// 	for (auto& token : line) {
	// 		std::cout << token << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	if (!this->_errors.empty()) {
		throw LexerException(this->_errors);
	}
	/*
	**Checking whether the user entered at least something
	*/
	if (areTokensEmpty()) {
		this->_errors += "You should have entered at least one command\n";
		throw LexerException(this->_errors);
	}
}

bool Lexer::areTokensEmpty() {
	if (this->_tokens.size() != 0) {
		return false;
	}
	return true;
}

void Lexer::lineValidation(std::string input) {
	std::smatch match;
	std::regex commandRegex("^\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?$");
	std::regex commandAndIntRegex("^\\s*(push|assert)\\s+(int8|int16|int32)\\(([-]?\\d+)\\)\\s*(?:;.*)?$");
	std::regex commandAndFloatingRegex("^\\s*(push|assert)\\s+(float|double)\\(([-]?\\d+\\.\\d+)\\)\\s*(?:;.*)?$");
	std::regex commentRegex("^\\s*(?:;.*){1}$");
	std::regex emptyLineRegex("^\\s*$");

	if (regex_search(input, match, commandRegex)) {
		processingShortCommands(match);
	} else if (regex_search(input, match, commandAndIntRegex) || regex_search(input, match, commandAndFloatingRegex)) {
		processingCommandsWithArguments(match);
	} else if (regex_search(input, match, commentRegex) || regex_search(input, match, emptyLineRegex)) {
		processingEmptyLinesAndComments();
	} else {
		this->_errors += "Lexer error: Check the syntax in the following line: \"" + input + "\"\n";
	}
}

void Lexer::processingShortCommands(std::smatch match) {
	std::vector<std::string> oneLineTokens;
	/*
	**pushing back only one token because there is only one
	*/
	oneLineTokens.push_back(match[1].str());
	/*
	**adding the result to the tokens vector
	*/
	this->_tokens.push_back(oneLineTokens);
}

void Lexer::processingCommandsWithArguments(std::smatch match) {
	std::vector<std::string> oneLineTokens;
	/*
	**push and assert have three tokens in them, hence 3 push backs
	*/
	oneLineTokens.push_back(match[1].str());
	oneLineTokens.push_back(match[2].str());
	oneLineTokens.push_back(match[3].str());
	/*
	**adding the result to the tokens vector
	*/
	this->_tokens.push_back(oneLineTokens);
}

void Lexer::processingEmptyLinesAndComments() {
	/*
	**this part is for future purposes
	**currently it does nothing as the comments and empty lines must be validated but are not used
	*/
	return;
}

const std::vector<std::vector<std::string>>& Lexer::getTokens() {
	return this->_tokens;
}
