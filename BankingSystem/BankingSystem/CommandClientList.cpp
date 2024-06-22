#include "CommandClientList.h"

int ListCommand::execute() {
	MyString bankName;
	std::cin >> bankName;
	try {
		User* curClient = app->getLogedUser();
		if (Client* cur = dynamic_cast<Client*>(curClient)) {
			cur->list(bankName);
		}
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
