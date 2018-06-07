#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

class Parser {
	public:
		Parser() = delete;
		Parser(const std::vector<std::vector<std::string>>& lexerTokens);
		Parser(const Parser& obj) = delete;
		~Parser();
		void printTokens();//TODO

		Parser& operator=(const Parser& obj) = delete;
	private:
		const std::vector<std::vector<std::string>>& _lexerTokens;
		std::string _errors;
		int exitCount;
		unsigned long numberOfTokenWithError = 0;

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
		void isExitLastCommand();
};

#endif
