#pragma once
#include "ACommadFactory.h"
#include "CommandThirdPartySendCheck.h"
#include "CommandWhoAmI.h"
#include "CommandHelp.h"
#include "CommandLogout.h"

class ThirdPartySessionCommandFactory : public CommandFactory {
	Command* getCommand() override {
		int n;
		std::cin >> n;
		switch (n)
		{
		case 1: return new SendCheckCommand(); break;
		case 2: return new WhoAmICommand(); break;
		case 3: return new HelpCommand(); break;
		case 4: return new LogoutCommand(); break;
		}
		return nullptr;
	}

	MyString getCommandsDescription() const
	{
		return "Choose: \n 1) sendCheck\n 2) whoami\n 3) help\n 4) logout\n";
	}
};