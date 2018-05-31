#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <iostream>

class Factory {
	public:
		Factory() = delete;
		Factory(Factory const& obj) = delete;
		~Factory();

		IOperand const* createOperand(eOperandType, std::string const& value) const;

		Factory& operator=(Factory const& obj) = delete;
	private:
		IOperand const* createInt8(std::string const& value) const;
		IOperand const* createInt16(std::string const& value) const;
		IOperand const* createInt32(std::string const& value) const;
		IOperand const* createFloat(std::string const& value) const;
		IOperand const* createDouble(std::string const& value) const;
};

#endif
