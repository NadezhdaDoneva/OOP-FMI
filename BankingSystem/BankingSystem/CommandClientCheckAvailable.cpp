#include "CommandClientCheckAvailable.h"

void CheckAvailableCommand::execute(Application* app) {
	MyString bankName;
	unsigned accountNumber = 0;
	std::cin >> bankName >> accountNumber;
	try {
		User* curClient = app->getLoggedUser();
		if (Client* cur = dynamic_cast<Client*>(curClient)) {
			double balance = cur->checkAvailable(bankName, accountNumber);
			std::cout << balance;
		}
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
