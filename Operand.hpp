// enum eOperandType {
// 	Int8 = 0,
// 	Int16,
// 	Int32,
// 	Float,
// 	Double
// };

// enum precision {
// 	Int8 = 0,
// 	Int16,
// 	Int32,
// 	Float,
// 	Double
// };

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include <string>

template<class T>
class Operand : public IOperand {
	public:
		Operand() = delete;
		Operand(eOperandType type, const std::string value);
		Operand(Operand const& obj) = delete;
		~Operand();

		const IOperand* operator+(IOperand const& rhs) const override;
		const IOperand* operator-(IOperand const& rhs) const override;
		const IOperand* operator*(IOperand const& rhs) const override;
		const IOperand* operator/(IOperand const& rhs) const override;
		const IOperand* operator%(IOperand const& rhs) const override;

		const std::string& toString() const override;
		int getPrecision() const override;
		eOperandType getType() const override;

		Operand& operator=(Operand const& obj) = delete;
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
const IOperand* Operand<T>::operator+(IOperand const& rhs) const {
	(void)rhs;
	return NULL;//todo
}

template<typename T>
const IOperand* Operand<T>::operator-(IOperand const& rhs) const {
	(void)rhs;
	return NULL;//todo
}

template<typename T>
const IOperand* Operand<T>::operator*(IOperand const& rhs) const {
	(void)rhs;
	return NULL;//todo
}

template<typename T>
const IOperand* Operand<T>::operator/(IOperand const& rhs) const {
	(void)rhs;
	return NULL;//todo
}

template<typename T>
const IOperand* Operand<T>::operator%(IOperand const& rhs) const {
	(void)rhs;
	return NULL;//todo
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
