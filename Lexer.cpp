#include "Lexer.hpp"
#include "LexerException.hpp"
#include <iostream>
#include <fstream>
#include <regex>

Lexer::Lexer() {
}

Lexer::Lexer(int argc, char* argv[]) {
	if (argc == 1) {
		/*
		**read stuff from the standard input
		**end at user's input == ";;"
		*/
		this->readFromStandardInput();
	} else if (argc == 2) {
		/*
		**read stuff from file
		**end at EOF
		*/
		this->readFromFile(argv[1]);
	} else {
		throw LexerException("There are too many arguments");
	}
}

Lexer::Lexer(Lexer const& obj) {
	*this = obj;
}

Lexer::~Lexer() {
}

void Lexer::readFromFile(char* file) {
	std::ifstream ifstr(file);
	if (!ifstr.is_open()) {
		throw LexerException("The stream is not opened");
	}

	std::string input;

	this->errors = "";
	while (std::getline(ifstr, input)) {
		this->lineValidation(input);
	}
	if (this->errors != "") {
		throw LexerException(errors);
	}
}

void Lexer::readFromStandardInput() {	
	std::string input;

	this->errors = "";
	while (std::getline(std::cin, input) && input != ";;") {
		this->lineValidation(input);
	}
	// std::cout << "output tokens:" << this->tokens.size() << std::endl;
	// for (auto& line : this->tokens) {
	// 	for (auto& token : line) {
	// 		std::cout << token << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	if (this->errors != "") {
		throw LexerException(errors);
	}
}

void Lexer::lineValidation(std::string input) {
	//std::cout << input << std::endl;
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
		this->errors += "Lexer error. Check the syntax in the following line: \"" + input + "\"\n";
	}

	// bool found = regex_search(input, match, commandAndIntRegex);
	// std::cout << (found ? "Found" : "Not found") << std::endl;
	// std::cout << "match.size() " << match.size() << std::endl;
	// for (unsigned long i = 0; i < match.size(); ++i){
	// 	std::cout << "match[" << i << "]: " << match[i].str() << std::endl;
	// }

	// bool match = regex_match(input, commandRegex);
	// std::cout << (match ? "Matched" : "Not matched") << std::endl;
}

void Lexer::processingShortCommands(std::smatch match) {
	std::vector<std::string> oneLineTokens;

	oneLineTokens.push_back(match[1].str());
	for (unsigned int i = 0; i < oneLineTokens.size(); ++i) {
		std::cout << oneLineTokens.at(i) << " ";
	}
	std::cout << std::endl;
	this->tokens.push_back(oneLineTokens);
}

void Lexer::processingCommandsWithArguments(std::smatch match) {
	std::vector<std::string> oneLineTokens;

	oneLineTokens.push_back(match[1].str());
	oneLineTokens.push_back(match[2].str());
	oneLineTokens.push_back(match[3].str());
	for (unsigned int i = 0; i < oneLineTokens.size(); ++i) {
		std::cout << oneLineTokens.at(i) << " ";
	}
	std::cout << std::endl;
	this->tokens.push_back(oneLineTokens);
	// std::cout << match[1].str() <<std::endl;
	// std::cout << match[2].str() <<std::endl;
	// std::cout << match[3].str() <<std::endl;
}

void Lexer::processingEmptyLinesAndComments() {
	/*
	**this part is for future purposes
	**currently it does nothing as the comments and empty lines must be validated but are not used
	*/
	return;
}

const std::vector<std::vector<std::string>>& Lexer::getTokens() {
	return this->tokens;
}

Lexer& Lexer::operator=(Lexer const& obj) {
	if (this != &obj) {
		//copy stuff
	}
	return *this;
}
