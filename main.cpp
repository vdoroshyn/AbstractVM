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
		// parser.printTokens();
		VirtualMachine VM(lexer.getTokens());
		// VM.printTokens();
	} catch (LexerException& e) {
		std::cout << e.what() << std::endl;
	} catch (ParserException& e) {
		std::cout << e.what() << std::endl;
	} catch (VirtualMachineException& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown exception was caught" << std::endl;
	}
	system("leaks avm");
	return 0;
}


//to fix:
//choosing the right type in operations
//modulo with fp
//mod and div on 0

//to add:
//usage
//