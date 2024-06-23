#include "CommandEmployeeApprove.h"

int ApproveCommand::execute() {
    int n;
    std::cin >> n;

	try {
		app->approve(n);
		std::cout << "You succcessfully approved. \n";
		return 2;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}

    return 0;
}
