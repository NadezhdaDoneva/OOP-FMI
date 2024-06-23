#include "CommandLogin.h"

int LoginCommand::execute() {
	MyString username, password;
	std::cout << "Input username: ";
	std::cin >> username;
	std::cout << "Input password: ";
	std::cin >> password;

	try {
		app->login(std::move(username), std::move(password));
		LoggedUserType loggedUserType = app->getType();
		std::cout << "User successfylly logged.\n";

		switch (loggedUserType)
		{
		case LoggedUserType::client:
			return 1;
		case LoggedUserType::employee:
			return 2;
		case LoggedUserType::thirdParty:
			return 3;
		}
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
