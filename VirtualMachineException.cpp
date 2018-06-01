#include "VirtualMachineException.hpp"

VirtualMachineException::VirtualMachineException() {
}

VirtualMachineException::VirtualMachineException(std::string const& error): _error(error) {
}

VirtualMachineException::VirtualMachineException(VirtualMachineException const& obj) {
	*this = obj;
}

VirtualMachineException& VirtualMachineException::operator=(VirtualMachineException const& obj) {
	if (this != &obj) {
		this->_error = obj._error;
	}
	return *this;
}

const char* VirtualMachineException::what() const noexcept {
	return this->_error.c_str();
}
