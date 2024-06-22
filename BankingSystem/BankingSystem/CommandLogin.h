#pragma once
#include "Command.h"

class LoginCommand : public Command {
public:
	LoginCommand() = default;

	LoginCommand(const LoginCommand&) = delete;
	LoginCommand& operator=(const LoginCommand&) = delete;

	int execute() override;
};
