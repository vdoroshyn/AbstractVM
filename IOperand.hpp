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

	virtual IOperand const* operator+(IOperand const& rhs) const = 0;
	virtual IOperand const* operator-(IOperand const& rhs) const = 0;
	virtual IOperand const* operator*(IOperand const& rhs) const = 0;
	virtual IOperand const* operator/(IOperand const& rhs) const = 0;
	virtual IOperand const* operator%(IOperand const& rhs) const = 0;

	virtual std::string const& toString() const = 0;
	virtual int getPrecision() const = 0;
	virtual eOperandType getType() const = 0;
};

#endif
