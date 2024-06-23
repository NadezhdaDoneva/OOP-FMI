#include "CommandEmployeeView.h"

int ViewCommand::execute() {
	unsigned num;
	std::cin >> num;
	try {
		app->viewTask(num);
		return 2;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
