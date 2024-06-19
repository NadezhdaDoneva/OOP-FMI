#pragma once
#include "Command.h"

class RegClientCommand : public Command {
public:
	RegClientCommand() = default;

	RegClientCommand(const RegClientCommand&) = delete;
	RegClientCommand& operator=(const RegClientCommand&) = delete;

	void execute(Application* app) override;
};