#include "CommandClientMessages.h"

void MessagesCommand::execute(Application* app) {
	try {
		User* curClient = app->getLoggedUser();
		if (Client* cur = dynamic_cast<Client*>(curClient)) {
			cur->printMessages();
		}
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
