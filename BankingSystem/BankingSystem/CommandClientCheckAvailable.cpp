#include "CommandClientCheckAvailable.h"

int CheckAvailableCommand::execute() {
	MyString bankName;
	unsigned accountNumber = 0;
	std::cin >> bankName >> accountNumber;
	try {
		double balance = app->checkAvailable(bankName, accountNumber);
		std::cout << balance;
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
