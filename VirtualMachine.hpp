#ifndef VIRTUAL_MACHINE_HPP
#define VIRTUAL_MACHINE_HPP

#include <string>
#include <vector>
#include <map>
#include "IOperand.hpp"

//make methods you can private
class VirtualMachine {
	public:
		/*
		**the map array is needed to convert strings to enum values
		*/
		std::map<std::string, eOperandType> enumMap;

		VirtualMachine() = delete;
		VirtualMachine(const std::vector<std::vector<std::string>>& lexerTokens);
		VirtualMachine(VirtualMachine const& obj) = delete;
		~VirtualMachine();

		void printTokens();//todo

		VirtualMachine& operator=(VirtualMachine const& obj) = delete;
	private:
		const std::vector<std::vector<std::string>>& _lexerTokens;
};

#endif
