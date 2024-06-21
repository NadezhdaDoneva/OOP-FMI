#pragma once
#include "Command.h"

class HandleThirdPartyCommand : public Command
{
public:
	HandleThirdPartyCommand() = default;

	HandleThirdPartyCommand(const HandleThirdPartyCommand&) = delete;
	HandleThirdPartyCommand& operator=(const HandleThirdPartyCommand&) = delete;

	void execute(Application* app) override;
};