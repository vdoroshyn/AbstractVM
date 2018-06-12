#include <sys/stat.h>
#include "Lexer.hpp"
#include "LexerException.hpp"
#include <iostream>
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
		**Showing usage to the user
		*/
		std::string argument = std::string(argv[1]);

		if (argument == "--help") {
			printOutUsage();
			std::exit(1);
		}
		/*
		**An Easter Egg for perverts in UNIT Factory
		**I am chrcking whether the file is regular in order to avoid different shenanigans
		*/
		if (!isFileRegular(argv[1])) {
			throw LexerException("Eric Exception: Congratulations! You are trying to check veeeeeery perverted cases!");
		}
		/*
		**read stuff from a file
		**end at EOF
		*/
		this->readFromFile(argv[1]);
	} else {
		throw LexerException("There are too many arguments.");
	}
}

Lexer::~Lexer() {
}

void Lexer::printOutUsage() {
	std::cout << "\033[0;34mThe program works either with no arguments (standard input with '\033[1;94m;;\033[0;34m' as the ending input) or with one argument (the file's name).\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95mcomments\033[0m: \033[0;34mComments start with a '\033[1;94m;\033[0;34m' symbol and end with a newline. A comment can be either at the start of a line or after an instruction.\033[0m" << std::endl << std::endl; 
	std::cout << "\033[1;95mpush v\033[0m: \033[0;34mPushes the value \033[1;94mv\033[0m \033[0;34mat the top of the stack. The value \033[1;94mv\033[0m \033[0;34mmust have one of the following forms:\033[0m" << std::endl;
	std::cout << "\t\033[1;94mint8(n) : \033[0;34mCreates a 8-bit integer with the value \033[1;94mn\033[0m." << std::endl;
	std::cout << "\t\033[1;94mint16(n) : \033[0;34mCreates a 16-bit integer with the value \033[1;94mn\033[0m." << std::endl;
	std::cout << "\t\033[1;94mint32(n) : \033[0;34mCreates a 32-bit integer with the value \033[1;94mn\033[0m." << std::endl;
	std::cout << "\t\033[1;94mfloat(z) : \033[0;34mCreates a float with the value \033[1;94mz\033[0m." << std::endl;
	std::cout << "\t\033[1;94mdouble(z) : \033[0;34mCreates a double with the value \033[1;94mz\033[0m." << std::endl << std::endl;
	std::cout << "\033[1;95mpop\033[0m: \033[0;34mUnstacks the value from the top of the stack. \033[1;91m" << std::endl << "If the stack is empty, the program execution stops with an error.\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95mdump\033[0m: \033[0;34mDisplays each value of the stack from the most recent one to the oldest one without changing the stack.\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95massert v\033[0m: \033[0;34mAsserts that the value at the top of the stack is equal to the one passed as the parameter for this instruction. \033[1;91m" << std::endl << "If it is not - the program execution stops with an error.\033[0m" << std::endl << "\033[0;34mThe value \033[1;94mv\033[0m \033[0;34mhas the same form that those passed as parameters to the command push.\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95madd\033[0m: \033[0;34mUnstacks the first two values in the stack, adds them together, and pushes the result on the stack. \033[1;91m" << std::endl << "If there are less than 2 operands in the stack, the program execution stops with an error.\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95msub\033[0m: \033[0;34mUnstacks the first two values in the stack, subtracts them, and pushes the result on the stack. \033[1;91m" << std::endl << "If there are less than 2 operands in the stack, the program execution stops with an error.\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95mmul\033[0m: \033[0;34mUnstacks the first two values in the stack, multiplies them, and pushes the result on the stack. \033[1;91m" << std::endl << "If there are less than 2 operands in the stack, the program execution stops with an error.\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95mdiv\033[0m: \033[0;34mUnstacks the first two values in the stack, divides them, and pushes the result on the stack. \033[1;91m" << std::endl << "If there are less than 2 operands in the stack or the divisor is equal to 0, the program execution stops with an error.\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95mmod\033[0m: \033[0;34mUnstacks the first two values in the stack, calculates the modulus, and pushes the result on the stack. \033[1;91m" << std::endl << "If there are less than 2 operands in the stack or the divisor is equal to 0, the program execution stops with an error.\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95mprint\033[0m: \033[0;34mAsserts that the value at the top of the stack is a 8-bit integer (\033[1;91mif not, check the instructions for assert\033[0m\033[0;34m);" << std::endl << "After that, it interprets it as an ASCII value and displays the corresponding character on the standard output.\033[0m" << std::endl << std::endl;
	std::cout << "\033[1;95mexit\033[0m: \033[0;34mTerminates the execution of the current program. \033[1;91m" << std::endl << "There must be only one exit command and it must be located at the end of the input.\033[0m" << std::endl;
}

int Lexer::isFileRegular(const char* path) {
	struct stat sb;

	if (stat(path, &sb) == 0 && S_ISREG(sb.st_mode)) {
		return true;
	}
	return false;
}

void Lexer::readFromFile(char* file) {
	std::ifstream ifstr(file);
	if (!ifstr.is_open()) {
		throw LexerException("The stream is not opened.");
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
		this->_errors += "You should have entered at least one command.\n";
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
		this->_errors += "You should have entered at least one command.\n";
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
		this->_errors += "Lexer error: Check the syntax on line " + std::to_string(this->numberOfLineWithError) + ": \"" + input + "\".\n";
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
