#pragma once
#include "Command.h"

class ListCommand : public Command {
public:
	ListCommand() = default;

	ListCommand(const ListCommand&) = delete;
	ListCommand& operator=(const ListCommand&) = delete;

	int execute() override;
};