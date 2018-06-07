#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string>
#include <algorithm>
#include <limits>
#include "VirtualMachineException.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"

template<class T>
class Operand : public IOperand {
	public:
		Operand() = delete;
		Operand(eOperandType type, const std::string value);
		Operand(const Operand& obj) = delete;
		~Operand();

		const IOperand* operator+(const IOperand& rhs) const override;
		const IOperand* operator-(const IOperand& rhs) const override;
		const IOperand* operator*(const IOperand& rhs) const override;
		const IOperand* operator/(const IOperand& rhs) const override;
		const IOperand* operator%(const IOperand& rhs) const override;

		const std::string& toString() const override;
		int getPrecision() const override;
		eOperandType getType() const override;

		Operand& operator=(const Operand& obj) = delete;
	private:
		int _precision;
		eOperandType _type;
		const std::string _value;
};

template<typename T>
Operand<T>::Operand(eOperandType type, const std::string value) : _precision(type), _type(type), _value(value) {
}

template<typename T>
Operand<T>::~Operand() {
}

template<typename T>
const IOperand* Operand<T>::operator+(const IOperand& rhs) const {
	eOperandType type = std::max(this->getType(), rhs.getType());
	long double a = std::stold(this->toString());
	long double b = std::stold(rhs.toString());
	long double res = a + b;
	T min = std::numeric_limits<T>::lowest();
	T max = std::numeric_limits<T>::max();
	if (res < min || max < res) {
		throw VirtualMachineException("VM Exception: The result of the operation exceeds the boundaries of both operands' types");
	}
	T resWithoutZeros = static_cast<T>(res);
	return OperandFactory::getFactory().createOperand(type, std::to_string(resWithoutZeros));
}

template<typename T>
const IOperand* Operand<T>::operator-(const IOperand& rhs) const {
	eOperandType type = std::max(this->getType(), rhs.getType());
	long double a = std::stold(this->toString());
	long double b = std::stold(rhs.toString());
	long double res = a - b;
	T min = std::numeric_limits<T>::lowest();
	T max = std::numeric_limits<T>::max();
	if (res < min || max < res) {
		throw VirtualMachineException("VM Exception: The result of the operation exceeds the boundaries of both operands' types");
	}
	T resWithoutZeros = static_cast<T>(res);
	return OperandFactory::getFactory().createOperand(type, std::to_string(resWithoutZeros));
}

template<typename T>
const IOperand* Operand<T>::operator*(const IOperand& rhs) const {
	eOperandType type = std::max(this->getType(), rhs.getType());
	long double a = std::stold(this->toString());
	long double b = std::stold(rhs.toString());
	long double res = a * b;
	T min = std::numeric_limits<T>::lowest();
	T max = std::numeric_limits<T>::max();
	if (res < min || max < res) {
		throw VirtualMachineException("VM Exception: The result of the operation exceeds the boundaries of both operands' types");
	}
	T resWithoutZeros = static_cast<T>(res);
	return OperandFactory::getFactory().createOperand(type, std::to_string(resWithoutZeros));
}

template<typename T>
const IOperand* Operand<T>::operator/(const IOperand& rhs) const {
	eOperandType type = std::max(this->getType(), rhs.getType());
	long double a = std::stold(this->toString());
	long double b = std::stold(rhs.toString());
	long double res = a / b;
	T min = std::numeric_limits<T>::lowest();
	T max = std::numeric_limits<T>::max();
	if (res < min || max < res) {
		throw VirtualMachineException("VM Exception: The result of the operation exceeds the boundaries of both operands' types");
	}
	T resWithoutZeros = static_cast<T>(res);
	return OperandFactory::getFactory().createOperand(type, std::to_string(resWithoutZeros));
}

template<typename T>
const IOperand* Operand<T>::operator%(const IOperand& rhs) const {
	eOperandType type = std::max(this->getType(), rhs.getType());
	long double a = std::stold(this->toString());
	long double b = std::stold(rhs.toString());
	long double res = (int)a % (int)b;//todo
	T min = std::numeric_limits<T>::lowest();
	T max = std::numeric_limits<T>::max();
	if (res < min || max < res) {
		throw VirtualMachineException("VM Exception: The result of the operation exceeds the boundaries of both operands' types");
	}
	T resWithoutZeros = static_cast<T>(res);
	return OperandFactory::getFactory().createOperand(type, std::to_string(resWithoutZeros));
}

template<typename T>
const std::string& Operand<T>::toString() const {
	return this->_value;
}

template<typename T>
int Operand<T>::getPrecision() const {
	return this->_precision;
}

template<typename T>
eOperandType Operand<T>::getType() const {
	return this->_type;
}

#endif
