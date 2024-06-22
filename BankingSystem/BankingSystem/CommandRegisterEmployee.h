#pragma once
#include "Command.h"

class RegEmployeeCommand : public Command {
public:
	RegEmployeeCommand() = default;

	RegEmployeeCommand(const RegEmployeeCommand&) = delete;
	RegEmployeeCommand& operator=(const RegEmployeeCommand&) = delete;

	int execute() override;
};