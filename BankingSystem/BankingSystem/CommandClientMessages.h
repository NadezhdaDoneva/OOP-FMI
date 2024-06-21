#pragma once
#include "Command.h"

class MessagesCommand : public Command {
	MessagesCommand() = default;

	MessagesCommand(const MessagesCommand&) = delete;
	MessagesCommand& operator=(const MessagesCommand&) = delete;

	void execute(Application* app) override;
};