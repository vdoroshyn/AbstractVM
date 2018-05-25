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

void Lexer::lineValidation(std::string input) {
	//std::cout << input << std::endl;
	std::regex e("\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?");
	
	bool match = regex_match(input, e);
	std::cout << (match ? "Matched" : "Not matched") << std::endl;
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
}

void Lexer::readFromStandardInput() {	
	std::string input;

	while (std::getline(std::cin, input) && input != ";;") {
		this->lineValidation(input);
	}
}

Lexer& Lexer::operator=(Lexer const& obj) {
	if (this != &obj) {
		//copy stuff
	}
	return *this;
}
