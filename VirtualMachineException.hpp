#ifndef VIRTUAL_MACHINE_EXCEPTION_HPP
#define VIRTUAL_MACHINE_EXCEPTION_HPP

#include <iostream>
#include <exception>

class VirtualMachineException : public std::exception {
	public:
		VirtualMachineException();
		VirtualMachineException(std::string const& error);
		VirtualMachineException(VirtualMachineException const& obj);
		~VirtualMachineException() noexcept = default;

		virtual const char* what() const noexcept;

		VirtualMachineException& operator=(VirtualMachineException const& obj);
	private:
		std::string _error;
};

#endif
