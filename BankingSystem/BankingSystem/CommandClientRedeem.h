#pragma once
#include "Command.h"

class RedeemCommand : public Command {
public:
	RedeemCommand() = default;

	RedeemCommand(const RedeemCommand&) = delete;
	RedeemCommand& operator=(const RedeemCommand&) = delete;

	int execute() override;
};