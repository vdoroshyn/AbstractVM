#include "OperandFactory.hpp"

OperandFactory::~OperandFactory() {
}

IOperand const* OperandFactory::createOperand(eOperandType, std::string const& value) const {
	//
}

IOperand const* OperandFactory::createInt8(std::string const& value) const {

}

IOperand const* OperandFactory::createInt16(std::string const& value) const {

}

IOperand const* OperandFactory::createInt32(std::string const& value) const {

}

IOperand const* OperandFactory::createFloat(std::string const& value) const {

}

IOperand const* OperandFactory::createDouble(std::string const& value) const {

}
