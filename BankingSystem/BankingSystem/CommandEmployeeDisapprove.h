#pragma once
#include "Command.h"

class DisapproveCommand : public Command {
public:
	DisapproveCommand() = default;

	DisapproveCommand(const DisapproveCommand&) = delete;
	DisapproveCommand& operator=(const DisapproveCommand&) = delete;

	int execute() override;
};