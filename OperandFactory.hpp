#ifndef OPERAND_FACTORY_HPP
#define OPERAND_FACTORY_HPP

#include "IOperand.hpp"
#include <string>

class OperandFactory {
	public:
		OperandFactory(OperandFactory const& obj) = delete;
		~OperandFactory();

		const IOperand* createOperand(eOperandType type, const std::string& value) const;

		static OperandFactory& getFactory();

		OperandFactory& operator=(const OperandFactory& obj) = delete;
	private:
		/*
		**array of pointers on member fucnctions
		*/
		const IOperand* (OperandFactory::*chooseYourOperand[5])(const std::string&) const;

		OperandFactory();

		const IOperand* createInt8(const std::string& value) const;
		const IOperand* createInt16(const std::string& value) const;
		const IOperand* createInt32(const std::string& value) const;
		const IOperand* createFloat(const std::string& value) const;
		const IOperand* createDouble(const std::string& value) const;
};

#endif
