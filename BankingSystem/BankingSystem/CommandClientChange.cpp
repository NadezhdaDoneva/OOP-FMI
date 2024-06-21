#include "CommandClientChange.h"

void ChangeCommand::execute(Application* app) {
	MyString newBankName, curBankName;
	unsigned accountNumber;
	std::cin >> newBankName >> curBankName >> accountNumber;

	try {
		app->change(newBankName, curBankName, accountNumber);
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
