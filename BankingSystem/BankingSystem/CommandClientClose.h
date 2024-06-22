#pragma once
#include "Command.h"

class CloseCommand : public Command {
public:
	CloseCommand() = default;

	CloseCommand(const CloseCommand&) = delete;
	CloseCommand& operator=(const CloseCommand&) = delete;

	int execute() override;
};