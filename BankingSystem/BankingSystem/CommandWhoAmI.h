#pragma once
#include "Command.h"

class WhoAmICommand : public Command {
public:
	WhoAmICommand() = default;

	WhoAmICommand(const WhoAmICommand&) = delete;
	WhoAmICommand& operator=(const WhoAmICommand&) = delete;

	int execute() override;
};