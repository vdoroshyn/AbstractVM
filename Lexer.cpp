#include "Lexer.hpp"
#include "LexerException.hpp"
#include <iostream>
#include <fstream>

Lexer::Lexer() {
}

Lexer::Lexer(int argc, char* argv[]) {
	if (argc == 1) {
		this->readFromStandardInput();
		//read stuff from the standard input
		//end at user's input == ";;"

	} else if (argc == 2) {
		this->readFromFile(argv[1]);
		//read stuff from file
		//end at EOF
		
	} else {
		throw LexerException("exception");
		// std::cout << "There are too many arguments" << std::endl;
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

	while (std::getline(ifstr, input)) {
		std::cout << input << std::endl;
	}
	std::cout << "file" << std::endl;
}

void Lexer::readFromStandardInput() {
	std::cout << "standard" << std::endl;
	std::string input;

	while (std::getline(std::cin, input) && input != ";;") {
		std::cout << input << std::endl;
	}
}

Lexer& Lexer::operator=(Lexer const& obj) {
	if (this != &obj) {
		//copy stuff
	}
	return *this;
}
