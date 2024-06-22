#include "CommandClientChange.h"

int ChangeCommand::execute() {
	MyString newBankName, curBankName;
	unsigned accountNumber;
	std::cin >> newBankName >> curBankName >> accountNumber;

	try {
		app->change(newBankName, curBankName, accountNumber);
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
