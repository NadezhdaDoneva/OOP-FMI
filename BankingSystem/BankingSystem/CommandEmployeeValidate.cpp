#include "CommandEmployeeValidate.h"

int ValidateCommand::execute() {
    int n;
    std::cin >> n;
	try {
		//TO Do
		//app->validate();
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
	return 2;
}
