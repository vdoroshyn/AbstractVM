#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string>
#include <map>
#include <algorithm>
#include <limits>
#include <math.h>
#include "VirtualMachineException.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <iostream>//todo
static std::map<eOperandType, long double> lowest {
	{ Int8, std::numeric_limits<int8_t>::lowest()   },
	{ Int16, std::numeric_limits<int16_t>::lowest() },
	{ Int32, std::numeric_limits<int32_t>::lowest() },
	{ Float, std::numeric_limits<float>::lowest()   },
	{ Double, std::numeric_limits<double>::lowest() },
};

static std::map<eOperandType, long double> biggest {
	{ Int8, std::numeric_limits<int8_t>::max()   },
	{ Int16, std::numeric_limits<int16_t>::max() },
	{ Int32, std::numeric_limits<int32_t>::max() },
	{ Float, std::numeric_limits<float>::max()   },
	{ Double, std::numeric_limits<double>::max() },
};

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
	/*
	**calculating the result of the operation
	*/
	long double res = a + b;
		std::cout << res << std::endl;
	/*
	**calculating the reuslting type depending on what operand is bigger
	*/
	auto min = lowest[type];
	auto max = biggest[type];
	std::cout << min << " " << max << std::endl;
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
	/*
	**calculating the result of the operation
	*/
	long double res = a - b;
	/*
	**calculating the reuslting type depending on what operand is bigger
	*/
	auto min = lowest[type];
	auto max = biggest[type];
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
	/*
	**calculating the result of the operation
	*/
	long double res = a * b;
	/*
	**calculating the reuslting type depending on what operand is bigger
	*/
	auto min = lowest[type];
	auto max = biggest[type];
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
	if (b == 0) {
		throw VirtualMachineException("VM Exception: Division by zero detected. Alert! Alert! Alert!");
	}
	/*
	**calculating the result of the operation
	*/
	long double res = a / b;
	/*
	**calculating the reuslting type depending on what operand is bigger
	*/
	auto min = lowest[type];
	auto max = biggest[type];
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
	if (b == 0) {
		throw VirtualMachineException("VM Exception: Modulo by zero detected. Alert! Alert! Alert!");
	}
	/*
	**calculating the result of the operation
	*/
	long double res = fmod(a, b);
	/*
	**calculating the reuslting type depending on what operand is bigger
	*/
	auto min = lowest[type];
	auto max = biggest[type];
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
