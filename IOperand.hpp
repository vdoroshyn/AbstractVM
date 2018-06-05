#ifndef I_OPERAND_HPP
#define I_OPERAND_HPP

#include <string>

enum eOperandType {
	Int8 = 0,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand {
public:
	virtual ~IOperand() {}

	virtual const IOperand* operator+(const IOperand& rhs) const = 0;
	virtual const IOperand* operator-(const IOperand& rhs) const = 0;
	virtual const IOperand* operator*(const IOperand& rhs) const = 0;
	virtual const IOperand* operator/(const IOperand& rhs) const = 0;
	virtual const IOperand* operator%(const IOperand& rhs) const = 0;

	virtual const std::string& toString() const = 0;
	virtual int getPrecision() const = 0;
	virtual eOperandType getType() const = 0;
};

#endif
