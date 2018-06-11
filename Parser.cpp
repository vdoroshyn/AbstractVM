#include "Parser.hpp"
#include "ParserException.hpp"
#include <limits>

Parser::Parser(const std::vector<std::vector<std::string>>& lexerTokens): _lexerTokens(lexerTokens) {
	this->exitCount = 0;
	this->checkTokens();
}

Parser::~Parser() {
}

void Parser::checkTokens() {
	for (unsigned long index = 0; index < this->_lexerTokens.size(); ++index) {
		/*
		**Iterating numberOfTokenWithError with each line to show relevant line sin error messages 
		*/
		++this->numberOfTokenWithError;

		if (isPush(index) || isAssert(index)) {
			validatePushAndAssertArgs(this->_lexerTokens[index]);
		} else if (isExit(index)) {
			/*
			**Incrementing exitCount each time there is an exit command
			*/
			++this->exitCount;
			checkExitCount();
		}
	}
	isExitLastCommand();
	if (!this->_errors.empty()) {
		throw ParserException(this->_errors);
	}
}

void Parser::validatePushAndAssertArgs(std::vector<std::string> tokenLine) {
	if (tokenLine[1] == "float") {
		validateFloatArgs(tokenLine[2]);
	} else if (tokenLine[1] == "double") {
		validateDoubleArgs(tokenLine[2]);
	} else if (tokenLine[1] == "int8") {
		validateInt8Args(tokenLine[2]);
	} else if (tokenLine[1] == "int16") {
		validateInt16Args(tokenLine[2]);
	} else if (tokenLine[1] == "int32") {
		validateInt32Args(tokenLine[2]);
	}
}

void Parser::validateFloatArgs(std::string token) {
	try {
		long double floatingPointNumber = std::stold(token);
		float fmin = std::numeric_limits<float>::lowest();
		float fmax = std::numeric_limits<float>::max();

		if (floatingPointNumber < fmin || fmax < floatingPointNumber) {
			this->_errors += "Parser error in token "
							+ std::to_string(this->numberOfTokenWithError) + ": \""
							+ token + "\" is out of float boundaries.\n";
		}
	} catch (std::invalid_argument) {
		this->_errors += "There was an error while converting a string to double.\n";
	} catch (std::out_of_range) {
		this->_errors += "Parser error in token "
						+ std::to_string(this->numberOfTokenWithError) + ": \""
						+ token + "\" is too big. Try to use such numbers in 10 years.\n";
	}
}

void Parser::validateDoubleArgs(std::string token) {
	try {
		long double floatingPointNumber = std::stold(token);
		double dmin = std::numeric_limits<double>::lowest();
		double dmax = std::numeric_limits<double>::max();

		if (floatingPointNumber < dmin || dmax < floatingPointNumber) {
			this->_errors += "Parser error in token " 
							+ std::to_string(this->numberOfTokenWithError) + ": \""
							+ token + "\" is out of double boundaries.\n";
		}
	} catch (std::invalid_argument) {
		this->_errors += "There was an error while converting a string to double.\n";
	} catch (std::out_of_range) {
		this->_errors += "Parser error in token "
						+ std::to_string(this->numberOfTokenWithError) + ": \""
						+ token + "\" is too big. Try to use such numbers in 10 years.\n";
	}
}

void Parser::validateInt8Args(std::string token) {
	try {
		long long int8Number = std::stoll(token);
		int8_t i8min = std::numeric_limits<int8_t>::lowest();
		int8_t i8max = std::numeric_limits<int8_t>::max();

		if (int8Number < i8min || i8max < int8Number) {
			this->_errors += "Parser error in token "
							+ std::to_string(this->numberOfTokenWithError) + ": \""
							+ token + "\" is out of int8 boundaries.\n";
		}
	} catch (std::invalid_argument) {
		this->_errors += "There was an error while converting a string to long long.\n";
	} catch (std::out_of_range) {
		this->_errors += "Parser error in token "
						+ std::to_string(this->numberOfTokenWithError) + ": \""
						+ token + "\" is too big. Try to use such numbers in 10 years.\n";
	}
}

void Parser::validateInt16Args(std::string token) {
	try {
		long long int16Number = std::stoll(token);
		int16_t i16min = std::numeric_limits<int16_t>::lowest();
		int16_t i16max = std::numeric_limits<int16_t>::max();

		if (int16Number < i16min || i16max < int16Number) {
			this->_errors += "Parser error in token "
							+ std::to_string(this->numberOfTokenWithError) + ": \""
							+ token + "\" is out of int16 boundaries.\n";
		}
	} catch (std::invalid_argument) {
		this->_errors += "There was an error while converting a string to long long.\n";
	} catch (std::out_of_range) {
		this->_errors += "Parser error in token "
						+ std::to_string(this->numberOfTokenWithError) + ": \""
						+ token + "\" is too big. Try to use such numbers in 10 years.\n";
	}
}

void Parser::validateInt32Args(std::string token) {
	try {
		long long int32Number = std::stoll(token);
		int32_t i32min = std::numeric_limits<int32_t>::lowest();
		int32_t i32max = std::numeric_limits<int32_t>::max();

		if (int32Number < i32min || i32max < int32Number) {
			this->_errors += "Parser error in token "
							+ std::to_string(this->numberOfTokenWithError) + ": \""
							+ token + "\" is out of int32 boundaries.\n";
		}
	} catch (std::invalid_argument) {
		this->_errors += "There was an error while converting a string to long long\n";
	} catch (std::out_of_range) {
		this->_errors += "Parser error in token "
						+ std::to_string(this->numberOfTokenWithError) + ": \""
						+ token + "\" is too big. Try to use such numbers in 10 years.\n";
	}
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
		this->_errors += "Parser error: You cannot have more than one exit.\n";
	} 
}

void Parser::isExitLastCommand() {
	unsigned long index = this->_lexerTokens.size() - 1;

	if (this->_lexerTokens[index][0] != "exit") {
		this->_errors += "Parser error: The last command should be exit.\n";
	}
}
