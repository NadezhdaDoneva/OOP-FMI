#pragma once
#include "Command.h"

class CheckAvailableCommand : public Command{
	CheckAvailableCommand() = default;

	CheckAvailableCommand(const CheckAvailableCommand&) = delete;
	CheckAvailableCommand& operator=(const CheckAvailableCommand&) = delete;

	void execute(Application* app) override;
};