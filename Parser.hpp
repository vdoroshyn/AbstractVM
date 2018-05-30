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
		void validateFloatArgs(std::string token);
		void validateDoubleArgs(std::string token);
		void validateInt8Args(std::string token);
		void validateInt16Args(std::string token);
		void validateInt32Args(std::string token);
		bool isPush(unsigned long index);
		bool isAssert(unsigned long index);
		bool isExit(unsigned long index);
		void checkExitCount();
		bool areTokensEmpty();
		void isExitLastCommand();

		Parser& operator=(Parser const& obj) = delete;
	private:
		const std::vector<std::vector<std::string>>& _lexerTokens;
		std::string _errors;
		int exitCount;
};

#endif
