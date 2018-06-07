#ifndef VIRTUAL_MACHINE_HPP
#define VIRTUAL_MACHINE_HPP

#include <string>
#include <vector>
#include <map>
#include "IOperand.hpp"

class VirtualMachine {
	public:
		VirtualMachine() = delete;
		VirtualMachine(const std::vector<std::vector<std::string>>& lexerTokens);
		VirtualMachine(const VirtualMachine& obj) = delete;
		~VirtualMachine();

		void printTokens();//todo
		void printOperands();//todo

		VirtualMachine& operator=(const VirtualMachine& obj) = delete;
	private:
		const std::vector<std::vector<std::string>>& _lexerTokens;
		std::vector<const IOperand*> _operands;
		/*
		**the map is needed to convert strings to enum values
		*/
		std::map<std::string, eOperandType> _eOperandTypeMap;
		/*
		**the map is needed to more easily call each command with arguments
		*/
		std::map<std::string, void (VirtualMachine::*)(const std::string& type, const std::string& value)> _commandsWithArgsMap;
		/*
		**the map is needed to more easily call each command without arguments
		*/
		std::map<std::string, void (VirtualMachine::*)()> _commandsMap;

		void run();
		void clearStack();
		
		void push(const std::string& type, const std::string& value);
		void pop();
		void dump();
		void assert(const std::string& type, const std::string& value);
		void add();
		void sub();
		void mul();
		void div();
		void mod();
		void print();
		void exit();
};

#endif
