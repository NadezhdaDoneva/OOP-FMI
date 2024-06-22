#include "CommandRegisterEmployee.h"

int RegEmployeeCommand::execute() {
	try {
		MyString username, egn, password, bankName;
		unsigned age;

		std::cout << "Input username: " << std::endl;
		std::cin >> username;
		std::cout << "Input egn: " << std::endl;
		std::cin >> egn;
		std::cout << "Input age: " << std::endl;
		std::cin >> age;
		std::cout << "Input password: " << std::endl;
		std::cin >> password;
		std::cout << "Input bank associated: " << std::endl;
		std::cin >> bankName;

		Employee employee(username, egn, age, password, bankName);
		app->registerEmployee(std::move(employee), bankName);
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
