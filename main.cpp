#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {

	if (argc == 1) {
		//read stuff from the standard input
		//end at user's input == ";;"
		std::cout << argv[0] << std::endl;

	} else if (argc == 2) {
		//read stuff from file
		//end at EOF
		std::cout << argv[1] << std::endl;
	} else {
		std::cout << "There are too many arguments" << std::endl;
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
