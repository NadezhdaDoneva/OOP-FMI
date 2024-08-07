#pragma once
#include "Command.h"

class OpenCommand : public Command {
public:
	OpenCommand() = default;

	OpenCommand(const OpenCommand&) = delete;
	OpenCommand& operator=(const OpenCommand&) = delete;

	int execute() override;
};