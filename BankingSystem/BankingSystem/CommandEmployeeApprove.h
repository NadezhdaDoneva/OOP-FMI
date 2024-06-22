#pragma once
#include "Command.h"

class ApproveCommand : public Command {
public:
	ApproveCommand() = default;

	ApproveCommand(const ApproveCommand&) = delete;
	ApproveCommand& operator=(const ApproveCommand&) = delete;

	int execute() override;
};