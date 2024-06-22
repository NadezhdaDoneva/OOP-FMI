#pragma once
#include "ACommadFactory.h"
//#include all thirdParty commands

class ThirdPartySessionCommandFactory : public CommandFactory {
	Command* getCommand() override {
		int n;
		std::cin >> n;
		//to switch with the thirdParty commands
		return nullptr;
	}

	MyString getCommandsDescription() const
	{
		return "Choose: \n 1) sendCheck\n 2) whoami\n 3) help\n  4) logout\n";
	}
};