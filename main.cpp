#include <iostream>//todo
#include <vector>//todo
#include "Lexer.hpp"
#include "LexerException.hpp"

int main(int argc, char* argv[]) {

	try {
		Lexer lexer = Lexer(argc, argv);
	} catch (LexerException& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown exception was caught" << std::endl;
	}


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
