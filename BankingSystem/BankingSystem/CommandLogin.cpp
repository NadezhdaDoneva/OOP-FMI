#include "CommandLogin.h"

void LoginCommand::execute(Application* app) {
	MyString username, password;
	std::cout << "Input username: ";
	std::cin >> username;
	std::cout << "Input password: ";
	std::cin >> password;

	app->login(std::move(username), std::move(password));
}
