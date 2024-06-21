#pragma once
#include "Command.h"

class HandleClientCommand : Command
{
public:
	HandleClientCommand() = default;

	HandleClientCommand(const HandleClientCommand&) = delete;
	HandleClientCommand& operator=(const HandleClientCommand&) = delete;

	void execute(Application* app) override;
};