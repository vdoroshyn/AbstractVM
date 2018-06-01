enum eOperandType {
	Int8 = 0,
	Int16,
	Int32,
	Float,
	Double
};

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
		Operand(Operand const& obj) = delete;
		~Operand();

		IOperand const* operator+(IOperand const& rhs) const override;
		IOperand const* operator-(IOperand const& rhs) const override;
		IOperand const* operator*(IOperand const& rhs) const override;
		IOperand const* operator/(IOperand const& rhs) const override;
		IOperand const* operator%(IOperand const& rhs) const override;

		std::string const& toString() const override;
		int getPrecision() const override;
		eOperandType getType() const override;

		Operand& operator=(Operand const& obj) = delete;
	private:
		int _precision;
		eOperandType _type;
};

template<typename T>
Operand<T>::~Operand() {
}

template<typename T>
IOperand const* Operand<T>::operator+(IOperand const& rhs) const {

}

template<typename T>
IOperand const* Operand<T>::operator-(IOperand const& rhs) const {
	
}

template<typename T>
IOperand const* Operand<T>::operator*(IOperand const& rhs) const {
	
}

template<typename T>
IOperand const* Operand<T>::operator/(IOperand const& rhs) const {
	
}

template<typename T>
IOperand const* Operand<T>::operator%(IOperand const& rhs) const {
	
}

template<typename T>
std::string Operand<T>::toString() const {
	//return the string representation
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
