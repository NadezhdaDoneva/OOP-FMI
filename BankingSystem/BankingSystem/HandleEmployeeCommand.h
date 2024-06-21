#pragma once
#include "Command.h"

class HandleEmployeeCommand : public Command
{
public:
	HandleEmployeeCommand() = default;

	HandleEmployeeCommand(const HandleEmployeeCommand&) = delete;
	HandleEmployeeCommand& operator=(const HandleEmployeeCommand&) = delete;

	void execute(Application* app) override;
};