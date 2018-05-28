#include "Parser.hpp"
#include "ParserException.hpp"

Parser::Parser(const std::vector<std::vector<std::string>>& lexerTokens): _lexerTokens(lexerTokens) {
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
}
