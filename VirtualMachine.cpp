#include "VirtualMachine.hpp"
#include "VirtualMachineException.hpp"
#include "OperandFactory.hpp"
#include <iostream>//todo

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

	// this->printTokens();
	this->run();
	// this->printOperands();
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::run() {
	try {
		for (auto& line : this->_lexerTokens) {
			if (line[0] == "push" || line[0] == "assert") {
				(this->*_commandsWithArgsMap[line[0]])(line[1], line[2]);
			} else {
				(this->*_commandsMap[line[0]])();
			}
		}
	} catch (VirtualMachineException &e) {
		this->clearStack();
		throw;
	}
}

void VirtualMachine::clearStack() {
	for (auto& ptr : this->_operands) {
		delete ptr;
	}
}

void VirtualMachine::push(const std::string& type, const std::string& value) {
	this->_operands.push_back(OperandFactory::getFactory().createOperand(this->_eOperandTypeMap[type], value));
}

void VirtualMachine::pop() {
	if (this->_operands.size() == 0) {
		throw VirtualMachineException("VM Exception: You are trying to call pop on an empty stack");
	}
	auto operand = *(this->_operands.end() - 1);
	this->_operands.pop_back();
	delete operand;
}

void VirtualMachine::dump() {
	if (this->_operands.size() == 0) {
		throw VirtualMachineException("VM Exception: You are trying to call dump on an empty stack");
	}
	for (auto it = this->_operands.rbegin(); it != this->_operands.rend(); ++it) {
		std::cout << (*it)->toString() << std::endl;
	}
}

void VirtualMachine::assert(const std::string& type, const std::string& value) {
	if (this->_operands.size() == 0) {
		throw VirtualMachineException("VM Exception: You are trying to call assert on an empty stack");
	}
	auto a = *(this->_operands.end() - 1);
	auto b = OperandFactory::getFactory().createOperand(this->_eOperandTypeMap[type], value);
	if (a->getType() != b->getType() || a->toString() != b->toString()) {
		delete b;
		throw VirtualMachineException("VM Exception: The two operands are not identical");
	}
	delete b;
}

void VirtualMachine::add() {
	if (this->_operands.size() < 2) {
		throw VirtualMachineException("VM Exception: There are less than 2 operands in the stack");
	}
	auto a = *(this->_operands.end() - 2);
	auto b = *(this->_operands.end() - 1);
	this->_operands.push_back(*a + *b);
	this->_operands.pop_back();
	this->_operands.pop_back();
	delete a;
	delete b;
}

void VirtualMachine::sub() {
	if (this->_operands.size() < 2) {
		throw VirtualMachineException("VM Exception: There are less than 2 operands in the stack");
	}
	auto a = *(this->_operands.end() - 2);
	auto b = *(this->_operands.end() - 1);
	this->_operands.push_back(*a - *b);
	this->_operands.pop_back();
	this->_operands.pop_back();
	delete a;
	delete b;
}

void VirtualMachine::mul() {
	if (this->_operands.size() < 2) {
		throw VirtualMachineException("VM Exception: There are less than 2 operands in the stack");
	}
	auto a = *(this->_operands.end() - 2);
	auto b = *(this->_operands.end() - 1);
	this->_operands.push_back(*a * *b);
	this->_operands.pop_back();
	this->_operands.pop_back();
	delete a;
	delete b;
}

void VirtualMachine::div() {
	if (this->_operands.size() < 2) {
		throw VirtualMachineException("VM Exception: There are less than 2 operands in the stack");
	}
	auto a = *(this->_operands.end() - 2);
	auto b = *(this->_operands.end() - 1);
	this->_operands.push_back(*a / *b);
	this->_operands.pop_back();
	this->_operands.pop_back();
	delete a;
	delete b;
}

void VirtualMachine::mod() {
	if (this->_operands.size() < 2) {
		throw VirtualMachineException("VM Exception: There are less than 2 operands in the stack");
	}
	auto a = *(this->_operands.end() - 2);
	auto b = *(this->_operands.end() - 1);
	this->_operands.push_back(*a % *b);
	this->_operands.pop_back();
	this->_operands.pop_back();
	delete a;
	delete b;
}
// push int32(32) 
// push int32(0) 
// div 
// exit 

void VirtualMachine::print() {
	if (this->_operands.size() == 0) {
		throw VirtualMachineException("VM Exception: You are trying to call print on an empty stack");
	}
	auto a = *(this->_operands.end() - 1);
	if (a->getPrecision() != Int8) {
		throw VirtualMachineException("VM Exception: The operand is not of type Int8");
	}
	char tempInt8 = std::stoi(a->toString());
	if (32 <= tempInt8 && tempInt8 <= 126) {
		std::cout << tempInt8 << std::endl;
	}
}

void VirtualMachine::exit() {
	this->clearStack();
	std::exit(0);
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
