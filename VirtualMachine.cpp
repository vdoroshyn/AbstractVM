#include "VirtualMachine.hpp"
#include "VirtualMachineException.hpp"
#include "OperandFactory.hpp"
#include <iostream>

VirtualMachine::VirtualMachine(const std::vector<std::vector<std::string>>& lexerTokens): _lexerTokens(lexerTokens) {
	/*
	**Populating the eOperandType map to convert strings to enum values
	*/
	this->_eOperandTypeMap["int8"] = Int8;
	this->_eOperandTypeMap["int16"] = Int16;
	this->_eOperandTypeMap["int32"] = Int32;
	this->_eOperandTypeMap["float"] = Float;
	this->_eOperandTypeMap["double"] = Double;
	/*
	**Populating the commandsWithArgs map to more easily call each command with arguments
	*/
	this->_commandsWithArgsMap["push"] = &VirtualMachine::push;
	this->_commandsWithArgsMap["assert"] = &VirtualMachine::assert;
	/*
	**Populating the commands map to more easily call each command without arguments
	*/
	this->_commandsMap["pop"] = &VirtualMachine::pop;
	this->_commandsMap["dump"] = &VirtualMachine::dump;
	this->_commandsMap["add"] = &VirtualMachine::add;
	this->_commandsMap["sub"] = &VirtualMachine::sub;
	this->_commandsMap["mul"] = &VirtualMachine::mul;
	this->_commandsMap["div"] = &VirtualMachine::div;
	this->_commandsMap["mod"] = &VirtualMachine::mod;
	this->_commandsMap["print"] = &VirtualMachine::print;
	this->_commandsMap["exit"] = &VirtualMachine::exit;
	// const IOperand* obj = OperandFactory::getFactory().createOperand(this->_eOperandTypeMap["float"], "45");
	// std::cout << obj->getType() << std::endl;
	// std::cout << obj->toString() << std::endl;
	// std::cout << obj->getPrecision() << std::endl;

	// this->printTokens();
	this->run();
	this->printOperands();
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::push(const std::string& type, const std::string& value) {
	std::cout << type << " " << value << std::endl;
	std::cout << "push" << std::endl;
	this->_operands.push_back(OperandFactory::getFactory().createOperand(this->_eOperandTypeMap[type], value));
}

void VirtualMachine::pop() {
	std::cout << "pop" << std::endl;
	if (this->_operands.size() == 0) {
		//throw
	}
	auto operand = *(this->_operands.end() - 1);
	this->_operands.pop_back();
	delete operand;
}

void VirtualMachine::dump() {
std::cout << "dump" << std::endl;
	if (this->_operands.size() == 0) {
		//throw
	}
	for (auto it = this->_operands.rbegin(); it != this->_operands.rend(); ++it) {
		std::cout << (*it)->toString() << std::endl;
	}
}

void VirtualMachine::assert(const std::string& type, const std::string& value) {
		std::cout << type << " " << value << std::endl;
	std::cout << "assert" << std::endl;
	(void)type;(void)value;
}

void VirtualMachine::add() {
std::cout << "add" << std::endl;
}

void VirtualMachine::sub() {
std::cout << "sub" << std::endl;
}

void VirtualMachine::mul() {
std::cout << "mul" << std::endl;
}

void VirtualMachine::div() {
std::cout << "div" << std::endl;
}

void VirtualMachine::mod() {
std::cout << "mod" << std::endl;
}

void VirtualMachine::print() {
std::cout << "print" << std::endl;
}

void VirtualMachine::exit() {
std::cout << "exit" << std::endl;
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

void VirtualMachine::printOperands() {
	for (auto& obj : this->_operands) {
		std::cout << "type: " << obj->getType() << ", string: " << obj->toString() << ", precision: " << obj->getPrecision() << std::endl;
	}
}//TODO

void VirtualMachine::run() {
	for (auto& line : this->_lexerTokens) {
		if (line[0] == "push" || line[0] == "assert") {
			(this->*_commandsWithArgsMap[line[0]])(line[1], line[2]);
		} else {
			(this->*_commandsMap[line[0]])();
		}
	}
}
