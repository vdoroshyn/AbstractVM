#include "Lexer.hpp"
#include "LexerException.hpp"
#include <iostream>

Lexer::Lexer() {
}

Lexer::Lexer(int argc, char* argv[]) {
	if (argc == 1) {
		//read stuff from the standard input
		//end at user's input == ";;"
		std::cout << argv[0] << std::endl;

	} else if (argc == 2) {
		//read stuff from file
		//end at EOF
		std::cout << argv[1] << std::endl;
	} else {
		throw LexerException("test");
		// std::cout << "There are too many arguments" << std::endl;
	}
}

Lexer::Lexer(Lexer const& obj) {
	*this = obj;
}

Lexer::~Lexer() {
}

Lexer& Lexer::operator=(Lexer const& obj) {
	if (this != &obj) {

	}
	return *this;
}
