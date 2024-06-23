#include "CommandEmployeeValidate.h"

int ValidateCommand::execute() {
    int n;
    std::cin >> n;
	try {
		app->validate(n);
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
	return 2;
}
