#include "VirtualMachine.hpp"
#include "VirtualMachineException.hpp"
#include "OperandFactory.hpp"
#include <iostream>

VirtualMachine::VirtualMachine(const std::vector<std::vector<std::string>>& lexerTokens): _lexerTokens(lexerTokens) {
	(void)this->_lexerTokens;//TODO
	std::cout << "success" << std::endl;
	/*
	**Populating the map array to convert strings to enum values
	*/
	this->enumMap["int8"] = Int8;
	this->enumMap["int16"] = Int16;
	this->enumMap["int32"] = Int32;
	this->enumMap["float"] = Float;
	this->enumMap["double"] = Double;
	const IOperand* obj = OperandFactory::getFactory().createOperand(this->enumMap["float"], "45");
	std::cout << obj->getType() << std::endl;
	std::cout << obj->toString() << std::endl;
	std::cout << obj->getPrecision() << std::endl;
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::printTokens() {
	std::cout << "VM: output number of lines with tokens: " << this->_lexerTokens.size() << std::endl;
	for (auto& line : this->_lexerTokens) {
		for (auto& token : line) {
			std::cout << token << " ";
		}
		std::cout << std::endl;
	}
}//TODO