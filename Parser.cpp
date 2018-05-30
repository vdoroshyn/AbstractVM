#include "Parser.hpp"
#include "ParserException.hpp"

Parser::Parser(const std::vector<std::vector<std::string>>& lexerTokens): _lexerTokens(lexerTokens) {
	this->exitCount = 0;
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
	for (unsigned long index = 0; index < this->_lexerTokens.size(); ++index) {
		if (isPush(index) || isAssert(index)) {
			validatePushAndAssertArgs(this->_lexerTokens[index]);
			//std::cout << this->_lexerTokens[i][2] << " ";
		} else if (isExit(index)) {
			/*
			**Incrementing exitCount each time there is an exit command
			*/
			++this->exitCount;
			checkExitCount();
		}
		// for (unsigned long j = 0; j < this->_lexerTokens[i].size(); ++j) {
		// 	std::cout << this->_lexerTokens[i][j] << " ";
		// }
	}
	isExitLastCommand();
	if (!this->_errors.empty()) {
		throw ParserException(this->_errors);
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
	std::cout << std::endl;
}

bool Parser::isPush(unsigned long index) {
	if (this->_lexerTokens[index][0] != "push") {
		return false;
	}
	return true;
}

bool Parser::isAssert(unsigned long index) {
	if (this->_lexerTokens[index][0] != "assert") {
		return false;
	}
	return true;
}

bool Parser::isExit(unsigned long index) {
	if (this->_lexerTokens[index][0] != "exit") {
		return false;
	}
	return true;
}

void Parser::checkExitCount() {
	if (this->exitCount > 1) {
		this->_errors += "Parser error. You cannot have more than one exit.\n";
	} 
}

void Parser::isExitLastCommand() {
	unsigned long index = this->_lexerTokens.size() - 1;

	if (this->_lexerTokens[index][0] != "exit") {
		this->_errors += "Parser error. The last command should be exit.\n";
	}
}

// bool Parser::validateFloatAndDoubleTokens(const std::vector<std::string> token) {

// }

