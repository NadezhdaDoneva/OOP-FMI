#include "CommandLogin.h"

int LoginCommand::execute() {
	MyString username, password;
	std::cout << "Input username: ";
	std::cin >> username;
	std::cout << "Input password: ";
	std::cin >> password;

	app->login(std::move(username), std::move(password)); //връща вида на потребителя, който се е логнал
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
