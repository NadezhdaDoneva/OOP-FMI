#pragma once
#include "Command.h"

class RunCommand : public Command {
	RunCommand() = default;

	RunCommand(const RunCommand&) = delete;
	RunCommand& operator=(const RunCommand&) = delete;

	void execute(Application* app) override;
};