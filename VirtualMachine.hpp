#ifndef VIRTUAL_MACHINE_HPP
#define VIRTUAL_MACHINE_HPP

#include <iostream>
#include <vector>
//make methods you can private
class VirtualMachine {
	public:
		VirtualMachine() = delete;
		VirtualMachine(const std::vector<std::vector<std::string>>& lexerTokens);
		VirtualMachine(VirtualMachine const& obj) = delete;
		~VirtualMachine();

		VirtualMachine& operator=(VirtualMachine const& obj) = delete;
	private:
		const std::vector<std::vector<std::string>>& _lexerTokens;
};

#endif
