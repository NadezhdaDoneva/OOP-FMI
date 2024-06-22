#pragma once
#include "ACommadFactory.h"
//#include all employee commands

class EmployeeSessionCommandFactory : public CommandFactory {
	Command* getCommand() override {
		int n;
		std::cin >> n;
		//to switch with the employee commands
		return nullptr;
	}

	MyString getCommandsDescription() const {
		return "Choose: \n 1) tasks\n 2) view [idx]\n 3) approve [idx]\n 4) disapprove [idx, message]\n 5) validate [idx]\n 7) whoami\n 8) help\n 9) logout\n";
	}
};