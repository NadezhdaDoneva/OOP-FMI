#include "CommandEmployeeTasks.h"

int TasksCommand::execute() {
	try {
		User* curEmployee = app->getLogedUser();
		if (!curEmployee) {
			std::cout << "No user is currently logged in." << std::endl;
			return -1;
		}
		if (Employee* cur = dynamic_cast<Employee*>(curEmployee)) {
			cur->printTasks();
			return 2;
		}
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
