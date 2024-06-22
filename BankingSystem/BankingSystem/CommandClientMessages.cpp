#include "CommandClientMessages.h"

int MessagesCommand::execute() {
	try {
		User* curClient = app->getLogedUser();
		if (Client* cur = dynamic_cast<Client*>(curClient)) {
			cur->printMessages();
		}
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
