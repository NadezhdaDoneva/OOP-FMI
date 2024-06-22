#pragma once
#include "Command.h"

class ValidateCommand : public Command {
public:
	ValidateCommand() = default;

	ValidateCommand(const ValidateCommand&) = delete;
	ValidateCommand& operator=(const ValidateCommand&) = delete;

	int execute() override;
};