#ifndef OPERAND_FACTORY_HPP
#define OPERAND_FACTORY_HPP

#include <string>

class OperandFactory {
	public:
		OperandFactory() = delete;
		OperandFactory(OperandFactory const& obj) = delete;
		~OperandFactory();

		IOperand const* createOperand(eOperandType, std::string const& value) const;

		OperandFactory& operator=(OperandFactory const& obj) = delete;
	private:
		IOperand const* createInt8(std::string const& value) const;
		IOperand const* createInt16(std::string const& value) const;
		IOperand const* createInt32(std::string const& value) const;
		IOperand const* createFloat(std::string const& value) const;
		IOperand const* createDouble(std::string const& value) const;
};

#endif
