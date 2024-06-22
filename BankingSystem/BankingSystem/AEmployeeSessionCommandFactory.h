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

	MyString getCommandsDescription() const
	{
		return "Choose: \n 1) tasks\n 2) view\n 3) approve\n 4) disapprove\n 5) validate\n 6) logout\n 7) exit\n";
	}
};