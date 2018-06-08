#include "Lexer.hpp"
#include "LexerException.hpp"
#include <iostream>//todo
#include <fstream>
#include <regex>

Lexer::Lexer(int argc, char* argv[]) {
	if (argc == 1) {
		/*
		**read stuff from the standard input
		**end at user's input == ";;"
		*/
		this->readFromStandardInput();
	} else if (argc == 2) {
		/*
		**An Easter Egg for perverts in UNIT Factory
		*/
		std::string argument = std::string(argv[1]);
		if (argument == "/dev/zero" || argument == "/dev/null") {
			throw LexerException("Eric Exception: Congratulations! You are trying to check veeeeeery perverted cases!");
		} else if (argument == "--help") {
			printOutUsage();
			std::exit(1);
		}
		/*
		**read stuff from a file
		**end at EOF
		*/
		this->readFromFile(argv[1]);
	} else {
		throw LexerException("There are too many arguments");
	}
}

Lexer::~Lexer() {
}

void Lexer::printOutUsage() {
	std::cout << "Comments: Comments start with a ';' symbol and finish with a newline. A comment can be either at the start of a line, or after an instruction." << std::endl; 
	std::cout << "\033[1;91mpush v\033[0m: Pushes the value v at the top of the stack. The value v must have one of the following form:" << std::endl;
	std::cout << "int8(n) : Creates an 8-bit integer with value n." << std::endl;
	std::cout << "int16(n) : Creates a 16-bit integer with value n." << std::endl;
	std::cout << "int32(n) : Creates a 32-bit integer with value n." << std::endl;
	std::cout << "float(z) : Creates a float with value z." << std::endl;
	std::cout << "double(z) : Creates a double with value z." << std::endl;
	std::cout << "pop: Unstacks the value from the top of the stack. If the stack is empty, the program execution must stop with an error." << std::endl;
	std::cout << "dump: Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack. Each value is separated from the next one by a newline." << std::endl;
	std::cout << "assert v: Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction. If it is not the case, the program execution must stop with an error. The value v has the same form that those passed as parameters to the instruction push." << std::endl;
	std::cout << "add: Unstacks the first two values on the stack, adds them together and stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error." << std::endl;
	std::cout << "sub: Unstacks the first two values on the stack, subtracts them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error." << std::endl;
	std::cout << "mul: Unstacks the first two values on the stack, multiplies them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error." << std::endl;
	std::cout << "div: Unstacks the first two values on the stack, divides them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover, if the divisor is equal to 0, the program execution must stop with an error too. Chatting about floating point values is relevant a this point. If you don’t understand why, some will understand. The linked question is an open one, there’s no definitive answer." << std::endl;
	std::cout << "mod: Unstacks the first two values on the stack, calculates the modulus, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover, if the divisor is equal to 0, the program execution must stop with an error too. Same note as above about fp values." << std::endl;
	std::cout << "print: Asserts that the value at the top of the stack is an 8-bit integer. (If not, see the instruction assert), then interprets it as an ASCII value and displays the corresponding character on the standard output." << std::endl;
	std::cout << "exit: Terminate the execution of the current program. If this instruction does not appears while all others instruction has been processed, the execution must stop with an error." << std::endl;
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
	if (!this->_errors.empty()) {
		throw LexerException(this->_errors);
	}
	/*
	**Checking whether the user entered at least something
	*/
	if (areTokensEmpty()) {
		this->_errors += "You should have entered at least one command\n";
		throw LexerException(this->_errors);
	}
}

void Lexer::readFromStandardInput() {	
	std::string input;

	while (std::getline(std::cin, input) && input != ";;") {
		this->lineValidation(input);
	}
	if (!this->_errors.empty()) {
		throw LexerException(this->_errors);
	}
	/*
	**Checking whether the user entered at least something
	*/
	if (areTokensEmpty()) {
		this->_errors += "You should have entered at least one command\n";
		throw LexerException(this->_errors);
	}
}

bool Lexer::areTokensEmpty() {
	if (this->_tokens.size() != 0) {
		return false;
	}
	return true;
}

void Lexer::lineValidation(std::string input) {
	std::smatch match;
	std::regex commandRegex("^\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?$");
	std::regex commandAndIntRegex("^\\s*(push|assert)\\s+(int8|int16|int32)\\(([-]?\\d+)\\)\\s*(?:;.*)?$");
	std::regex commandAndFloatingRegex("^\\s*(push|assert)\\s+(float|double)\\(([-]?\\d+\\.\\d+)\\)\\s*(?:;.*)?$");
	std::regex commentRegex("^\\s*(?:;.*){1}$");
	std::regex emptyLineRegex("^\\s*$");
	/*
	**Iterating numberOfLineWithError with each line to show relevant line sin error messages 
	*/
	++this->numberOfLineWithError;

	if (regex_search(input, match, commandRegex)) {
		processingShortCommands(match);
	} else if (regex_search(input, match, commandAndIntRegex) || regex_search(input, match, commandAndFloatingRegex)) {
		processingCommandsWithArguments(match);
	} else if (regex_search(input, match, commentRegex) || regex_search(input, match, emptyLineRegex)) {
		processingEmptyLinesAndComments();
	} else {
		this->_errors += "Lexer error: Check the syntax on line " + std::to_string(this->numberOfLineWithError) + ": \"" + input + "\"\n";
	}
}

void Lexer::processingShortCommands(std::smatch match) {
	std::vector<std::string> oneLineTokens;
	/*
	**pushing back only one token because there is only one
	*/
	oneLineTokens.push_back(match[1].str());
	/*
	**adding the result to the tokens vector
	*/
	this->_tokens.push_back(oneLineTokens);
}

void Lexer::processingCommandsWithArguments(std::smatch match) {
	std::vector<std::string> oneLineTokens;
	/*
	**push and assert have three tokens in them, hence 3 push backs
	*/
	oneLineTokens.push_back(match[1].str());
	oneLineTokens.push_back(match[2].str());
	oneLineTokens.push_back(match[3].str());
	/*
	**adding the result to the tokens vector
	*/
	this->_tokens.push_back(oneLineTokens);
}

void Lexer::processingEmptyLinesAndComments() {
	/*
	**this part is for future purposes
	**currently it does nothing as the comments and empty lines must be validated but are not used
	*/
	return;
}

const std::vector<std::vector<std::string>>& Lexer::getTokens() {
	return this->_tokens;
}
