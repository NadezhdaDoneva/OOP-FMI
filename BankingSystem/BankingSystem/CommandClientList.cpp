#include "CommandClientList.h"

int ListCommand::execute() {
	MyString bankName;
	std::cin >> bankName;
	try {
		app->list(bankName);
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
