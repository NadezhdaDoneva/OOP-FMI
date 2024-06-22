#pragma once
#include "Command.h"

class HandleNoneCommand : public Command
{
public:
	HandleNoneCommand() = default;

	HandleNoneCommand(const HandleNoneCommand&) = delete;
	HandleNoneCommand& operator=(const HandleNoneCommand&) = delete;

	int execute() override;
};