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
	// (void)argc;(void)argv;
	// eOperandType test = Int32;
	// std::cout << test << std::endl;

	// std::vector<int> testVector;

	// testVector.push_back(3);
	// testVector.push_back(4);
	// testVector.push_back(5);
	// std::cout << "Vector: ";

	// for (unsigned int i = 0; i < testVector.size(); ++i) {
	// 	std::cout << testVector.at(i) << " ";
	// }

	// std::cout << std::endl;
	return 0;
}


//to add:
//line 1, 2, 3
//usage
//