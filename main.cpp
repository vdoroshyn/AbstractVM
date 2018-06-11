#include <iostream>
#include "Lexer.hpp"
#include "LexerException.hpp"
#include "Parser.hpp"
#include "ParserException.hpp"
#include "VirtualMachine.hpp"
#include "VirtualMachineException.hpp"

int main(int argc, char* argv[]) {
	try {
		Lexer lexer(argc, argv);
		Parser parser(lexer.getTokens());
		VirtualMachine VM(lexer.getTokens());
	} catch (LexerException& e) {
		std::cout << e.what() << std::endl;
	} catch (ParserException& e) {
		std::cout << e.what() << std::endl;
	} catch (VirtualMachineException& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown exception was caught" << std::endl;
	}
	return 0;
}
