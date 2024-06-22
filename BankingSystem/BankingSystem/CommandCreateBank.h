#pragma once
#include "Command.h"

class CreateBankCommand : public Command {
public:
	CreateBankCommand() = default;

	CreateBankCommand(const CreateBankCommand&) = delete;
	CreateBankCommand& operator=(const CreateBankCommand&) = delete;

	void execute(Application* app) override;
};