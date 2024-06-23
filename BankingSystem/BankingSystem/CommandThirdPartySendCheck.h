#pragma once
#include "Command.h"

class SendCheckCommand : public Command {
public:
	SendCheckCommand() = default;

	SendCheckCommand(const SendCheckCommand&) = delete;
	SendCheckCommand& operator=(const SendCheckCommand&) = delete;

	int execute() override;
};