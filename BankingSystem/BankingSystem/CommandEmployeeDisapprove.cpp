#include "CommandEmployeeDisapprove.h"

int DisapproveCommand::execute() {
    int id;
    MyString mess;
    std::cin >> id >> mess;

	try {
		app->disapprove(id, mess);
		return 2;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
