#include "CommandLogout.h"

int LogoutCommand::execute() {
	try {
		app->logout();
		return 0;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
