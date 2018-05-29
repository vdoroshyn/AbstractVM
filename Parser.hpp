#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>

class Parser {
	public:
		Parser() = delete;
		Parser(const std::vector<std::vector<std::string>>& lexerTokens);
		Parser(Parser const& obj) = delete;
		~Parser();
		void printTokens();//TODO
		void checkTokens();
		void validatePushAndAssertArgs(std::vector<std::string> tokenLine);
		
		Parser& operator=(Parser const& obj) = delete;
	private:
		const std::vector<std::vector<std::string>>& _lexerTokens;
		std::string _errors;
		bool isExit;
};

#endif
