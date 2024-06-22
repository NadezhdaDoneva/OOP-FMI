#pragma once
#include "Command.h"

class ViewCommand : public Command {
public:
	ViewCommand() = default;

	ViewCommand(const ViewCommand&) = delete;
	ViewCommand& operator=(const ViewCommand&) = delete;

	void execute(Application* app) override;
};