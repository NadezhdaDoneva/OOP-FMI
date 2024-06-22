#include "CommandEmployeeView.h"

void ViewCommand::execute(Application* app) {
	unsigned num;
	std::cin >> num;
	try {
		/*User* curEmployee = app->getLoggedUser();
		if (Employee* cur = dynamic_cast<Employee*>(curEmployee)) {
			cur->viewTask(num);
		}*/
		app->viewTask(num);
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
