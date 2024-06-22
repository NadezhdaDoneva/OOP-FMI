#pragma once
#include "Command.h"

class RegisterCommand : public Command
{
public:
	RegisterCommand() = default;

	RegisterCommand(const RegisterCommand&) = delete;
	RegisterCommand& operator=(const RegisterCommand&) = delete;

	int execute() override;
};