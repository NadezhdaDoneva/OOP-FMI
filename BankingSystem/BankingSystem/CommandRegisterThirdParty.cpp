#include "CommandRegisterThirdParty.h"

int RegThirdPartyCommand::execute() {
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

		ThirdParty thirdParty(username, egn, age, password);
		app->registerThirdParty(std::move(thirdParty));
		std::cout << "User successfully registered.\n";
		return 0;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}
