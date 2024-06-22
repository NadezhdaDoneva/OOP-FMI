#include "CommandEmployeeView.h"

int ViewCommand::execute() {
	unsigned num;
	std::cin >> num;
	try {
		/*User* curEmployee = app->getLoggedUser();
		if (Employee* cur = dynamic_cast<Employee*>(curEmployee)) {
			cur->viewTask(num);
		}*/
		app->viewTask(num);
		return 2;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
