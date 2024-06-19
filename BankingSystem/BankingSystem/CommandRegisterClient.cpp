#include "CommandRegisterClient.h"

void RegClientCommand::execute(Application* app) {
	try {
		MyString username, egn, password;
		unsigned age;

		std::cout << "Input username: " << std::endl;
		std::cin >> username;
		std::cout << "Input egn: " << std::endl;
		std::cin >> egn;
		std::cout << "Input age: " << std::endl;
		std::cin >> age;
		std::cout << "Input password: " << std::endl;
		std::cin >> password;

		Client client(username, egn, age, password);
		app->registerClient(std::move(client));
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}
