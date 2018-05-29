#include "Parser.hpp"
#include "ParserException.hpp"

Parser::Parser(const std::vector<std::vector<std::string>>& lexerTokens): _lexerTokens(lexerTokens) {
	this->isExit = 0;
	this->checkTokens();
}

Parser::~Parser() {
}

void Parser::printTokens() {
	std::cout << "output number of lines with tokens: " << this->_lexerTokens.size() << std::endl;
	for (auto& line : this->_lexerTokens) {
		for (auto& token : line) {
			std::cout << token << " ";
		}
		std::cout << std::endl;
	}
}//TODO

void Parser::checkTokens() {
	std::cout << "output number of lines with tokens: " << this->_lexerTokens.size() << std::endl;
	for (unsigned long i = 0; i < this->_lexerTokens.size(); ++i) {
		if (this->_lexerTokens[i][0] == "push" || this->_lexerTokens[i][0] == "assert") {
			validatePushAndAssertArgs(this->_lexerTokens[i]);
			//std::cout << this->_lexerTokens[i][2] << " ";
		} else if (this->_lexerTokens[i][0] == "exit") {
			std::cout << "exit here";
		}
		// for (unsigned long j = 0; j < this->_lexerTokens[i].size(); ++j) {
		// 	std::cout << this->_lexerTokens[i][j] << " ";
		// }
		std::cout << std::endl;
	}
}

void Parser::validatePushAndAssertArgs(std::vector<std::string> tokenLine) {
	if (tokenLine[1] == "float" || tokenLine[1] == "double") {
		//work with floats and doubles
		std::cout << tokenLine[2] << " ";
	} else {
		//work with ints
		std::cout << tokenLine[2] << " ";
	}
}


// bool Parser::validateFloatAndDoubleTokens(const std::vector<std::string> token) {

// }

