#include "CommandClientClose.h"

void CloseCommand::execute(Application* app) {
	MyString bankName;
	unsigned accountNumber;
	std::cin >> bankName >> accountNumber;

	try {
		app->close(bankName, accountNumber);
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
