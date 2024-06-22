#pragma once
#include "Command.h"

class HelpCommand : public Command {
public:
	HelpCommand() = default;

	HelpCommand(const HelpCommand&) = delete;
	HelpCommand& operator=(const HelpCommand&) = delete;

	int execute() override;
};