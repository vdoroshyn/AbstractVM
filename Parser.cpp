#include "Parser.hpp"
#include "ParserException.hpp"

Parser::Parser(const std::vector<std::vector<std::string>>& lexerTokens): _lexerTokens(lexerTokens) {
}

Parser::~Parser() {
}

void Parser::foo() {
	(void)_lexerTokens;
}
