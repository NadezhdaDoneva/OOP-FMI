#pragma once
#include "ACommadFactory.h"
#include "CommandEmployeeTasks.h"
#include "CommandEmployeeView.h"
#include "CommandEmployeeApprove.h"
#include "CommandEmployeeDisapprove.h"
#include "CommandEmployeeValidate.h"
#include "CommandWhoAmI.h"
#include "CommandHelp.h"
#include "CommandLogout.h"

class EmployeeSessionCommandFactory : public CommandFactory {
	Command* getCommand() override {
		int n;
		std::cin >> n;
		
		switch (n)
		{
		case 1: return new TasksCommand(); break;
		case 2: return new ViewCommand(); break;
		case 3: return new ApproveCommand(); break;
		case 4: return new DisapproveCommand(); break;
		case 5: return new ValidateCommand(); break;
		case 6: return new WhoAmICommand(); break;
		case 7: return new HelpCommand(); break;
		case 8: return new LogoutCommand(); break;
		default:
			std::cout << "Unknown command!\n"; break;
		}
		return nullptr;
	}

	MyString getCommandsDescription() const {
		return "Choose: \n 1) tasks\n 2) view [idx]\n 3) approve [idx]\n 4) disapprove [idx, message]\n 5) validate [idx]\n 6) whoami\n 7) help\n 8) logout\n";
	}
};