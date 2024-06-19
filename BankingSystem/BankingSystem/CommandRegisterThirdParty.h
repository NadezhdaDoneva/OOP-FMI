#pragma once
#include "Command.h"

class RegThirdPartyCommand : public Command {
public:
	RegThirdPartyCommand() = default;

	RegThirdPartyCommand(const RegThirdPartyCommand&) = delete;
	RegThirdPartyCommand& operator=(const RegThirdPartyCommand&) = delete;

	void execute(Application* app) override;
};