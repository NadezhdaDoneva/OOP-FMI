#pragma once
#include "Command.h"

class ChangeCommand : public Command {
public:
	ChangeCommand() = default;

	ChangeCommand(const ChangeCommand&) = delete;
	ChangeCommand& operator=(const ChangeCommand&) = delete;

	int execute() override;
};