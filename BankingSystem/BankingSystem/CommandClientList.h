#pragma once
#include "Command.h"

class ListCommand : public Command {
	ListCommand() = default;

	ListCommand(const ListCommand&) = delete;
	ListCommand& operator=(const ListCommand&) = delete;

	void execute(Application* app) override;
};