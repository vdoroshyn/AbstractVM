#include "Operand.hpp"
#include "OperandFactory.hpp"

OperandFactory::OperandFactory()
	: chooseYourOperand {
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble
	}
{
}

OperandFactory::~OperandFactory() {
}

const IOperand* OperandFactory::createOperand(eOperandType type, const std::string& value) const {
	return (this->*chooseYourOperand[type])(value);
}

const IOperand* OperandFactory::createInt8(const std::string& value) const {
	return new Operand<int8_t>(Int8, value);
}

const IOperand* OperandFactory::createInt16(const std::string& value) const {
	return new Operand<int16_t>(Int16, value);
}

const IOperand* OperandFactory::createInt32(const std::string& value) const {
	return new Operand<int32_t>(Int32, value);
}

const IOperand* OperandFactory::createFloat(const std::string& value) const {
	return new Operand<float>(Float, value);
}

const IOperand* OperandFactory::createDouble(const std::string& value) const {
	return new Operand<double>(Double, value);
}

OperandFactory& OperandFactory::getFactory() {
	static OperandFactory _factory;

	return _factory;
}
