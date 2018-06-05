#include "VirtualMachineException.hpp"

VirtualMachineException::VirtualMachineException() {
}

VirtualMachineException::VirtualMachineException(const std::string& error): _error(error) {
}

VirtualMachineException::VirtualMachineException(const VirtualMachineException& obj) {
	*this = obj;
}

VirtualMachineException& VirtualMachineException::operator=(const VirtualMachineException& obj) {
	if (this != &obj) {
		this->_error = obj._error;
	}
	return *this;
}

const char* VirtualMachineException::what() const noexcept {
	return this->_error.c_str();
}
