#include "CommandEmployeeTasks.h"

void TasksCommand::execute(Application* app) {
	try {
		User* curEmployee = app->getLoggedUser();
		if (Employee* cur = dynamic_cast<Employee*>(curEmployee)) {
			cur->printTasks();
		}
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
