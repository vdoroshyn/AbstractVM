#include "VirtualMachine.hpp"
#include "VirtualMachineException.hpp"

VirtualMachine::VirtualMachine(const std::vector<std::vector<std::string>>& lexerTokens): _lexerTokens(lexerTokens) {
	(void)this->_lexerTokens;//TODO
}

VirtualMachine::~VirtualMachine() {
}
