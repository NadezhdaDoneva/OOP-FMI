#pragma once
#include "Command.h"

class MessagesCommand : public Command {
public:
	MessagesCommand() = default;

	MessagesCommand(const MessagesCommand&) = delete;
	MessagesCommand& operator=(const MessagesCommand&) = delete;

	int execute() override;
};