#pragma once
#include "Command.h"

class TasksCommand : public Command {
public:
	TasksCommand() = default;

	TasksCommand(const TasksCommand&) = delete;
	TasksCommand& operator=(const TasksCommand&) = delete;

	int execute() override;
};