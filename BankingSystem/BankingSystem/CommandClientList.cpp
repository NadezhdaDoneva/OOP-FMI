#include "CommandClientList.h"

void ListCommand::execute(Application* app) {
	MyString bankName;
	std::cin >> bankName;
	try {
		User* curClient = app->getLoggedUser();
		if (Client* cur = dynamic_cast<Client*>(curClient)) {
			cur->list(bankName);
		}
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
