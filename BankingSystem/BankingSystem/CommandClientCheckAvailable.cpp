#include "CommandClientCheckAvailable.h"

int CheckAvailableCommand::execute() {
	MyString bankName;
	unsigned accountNumber = 0;
	std::cin >> bankName >> accountNumber;
	try {
		User* curClient = app->getLogedUser();
		if (Client* cur = dynamic_cast<Client*>(curClient)) {
			double balance = cur->checkAvailable(bankName, accountNumber);
			std::cout << balance;
		}
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
